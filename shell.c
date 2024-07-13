#include "main.h"

/**
 * main - the main program
 * @argc: number of command line arguments
 * @argv: array of strings, each string represents a command line argument
 * Return: void
 */
int main(int argc, char **argv)
{
	char *user_input;
	int status = 0;
	(void)argc;
	signal(SIGINT, _signal);
	if (argv[1])
	{
		status = file_as_input(argv);
	}
	else
	{
		do {
			user_input = read_line();
			if (user_input != NULL)
			{
				status = shell(user_input, status);
			}
			else
				break;

		} while (true);
	}

	return (status);
}

/**
 * shell - process and executes user input
 * @user_input: user input
 * @prev_status: return status of the previous command
 * Return: exit status
 */
int shell(char *user_input, int prev_status)
{
	char **args = NULL;
	int status = prev_status;

	shell_exit(user_input);
	is_comment(user_input);
	if (strstr(user_input, "&&") || strstr(user_input, "||"))
	{
		status = logical_ope(user_input);
	}
	else if (strchr(user_input, ';') != NULL)
	{
		status = is_colon(user_input);
	}
	else if (strstr(user_input, "setenv") || strstr(user_input, "unsetenv"))
	{
		args = shell_split_line(user_input);
		set_unset(args);
	}
	else
	{
		args = shell_split_line(user_input);
		status = shell_launch(user_input, args, status);
	}

	free_mem(user_input, args);

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
 * set_unset - This function sets or un_sets environment variables
 *
 * @args: The arguments passed to the function
 *
 * Return: void
 */
void set_unset(char **args)
{
	int i;

	for (i = 0; args[i]; i++)
	{
		if (_strcmp(args[i], "setenv") == 0)
		{
			if (args[i + 2] == NULL && setenv(args[i + 1], "", 1) != 0)
			{
				dprintf(2, "Failed to set environment variable\n");
			}
			else if (args[i + 2] != NULL && setenv(args[i + 1], args[i + 2], 1) != 0)
			{
				dprintf(2, "Failed to set environment variable\n");
			}
		}
		else if (_strcmp(args[i], "unsetenv") == 0)
		{
			if (unsetenv(args[i + 1]) != 0)
			{
				dprintf(2, "Failed to unset environment variable\n");
			}
		}
		else if (array_len(args) == 1 && _strcmp(args[i], "env") == 0)
		{
			system(args[i]);
		}
	}
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
