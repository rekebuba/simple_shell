#include "main.h"

/**
 * main - the main program
 * @argc: number of command line arguments
 * @argv: array of strings, each string represents a command line argument
 * Return: void
 */
int main(int argc, char **argv)
{
	char *user_input = NULL;
	struct Node *head = NULL;
	int status = 0;

	(void)argc;

	signal(SIGINT, _signal);
	if (argv[1])
		status = file_as_input(head, argv);
	else
	{
		do {
			user_input = read_line(user_input);
			if (user_input)
			{
				status = shell(&head, user_input, status);
				free(user_input);
			}
			else
				break;

		} while (true);
	}

	freeList(head);

	return (status);
}

/**
 * shell - process and executes user input
 * @head: head of a single linked list that contains aliases
 * @user_input: user input
 * @prev_status: return status of the previous command
 * Return: exit status
 */
int shell(struct Node **head, char *user_input, int prev_status)
{
	char **args = NULL;
	int status = prev_status;

	shell_exit(head, user_input, prev_status);
	is_comment(user_input);
	if (strstr(user_input, "&&") || strstr(user_input, "||"))
		status = logical_ope(head, user_input);
	else if (strchr(user_input, ';'))
		status = is_colon(head, user_input);
	else if (strstr(user_input, "setenv") || strstr(user_input, "unsetenv"))
	{
		args = shell_split_line(head, user_input);
		set_unset_env(args);
	}
	else
	{
		args = shell_split_line(head, user_input);
		status = shell_launch(head, user_input, args, status);
	}

	free(args);

	return (status);
}

/**
 * file_as_input - file with all the commands that the shell run before exiting
 * @head: head of a single linked list that contains aliases
 * @args: the argument passed
 * Return: status
 */
int file_as_input(struct Node *head, char **args)
{
	char *file_name = args[1];
	char *line = NULL;
	int status = 0;
	size_t len = 0;
	FILE *file;

	file = fopen(file_name, "r");
	if (file == NULL)
	{
		dprintf(2, "./hsh: 0: Can't open %s\n", file_name);
		return (127);
	}

	/* Read one line at a time */
	while (get_line(&line, &len, file) != -1)
	{
		/* Process the line */
		status = shell(&head, line, status);
	}

	/* Close the file */
	fclose(file);
	free(line);

	return (status);
}

/**
 * free_mem - uses to free all allocated memory
 * @user_input: users input
 * @args: arguments
 * Return: void
 */
void free_mem(char *user_input, char **args)
{
	free(user_input);
	free(args);
}

/**
 * _signal - handle Ctr+C
 * @signal: when the Ctrl+c is received
 * Return: Void
 */
void _signal(int signal)
{
	(void)signal;
	printf("\n$ ");
	fflush(stdout);
}
