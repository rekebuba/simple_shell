#include "main.h"

/**
 * main - the main program
 * Return: void
 */
int main(void)
{
	char *user_input;
	char **args;
	int status = 0;

	signal(SIGINT, _signal);
	do {
		user_input = read_line();
		if (user_input != NULL)
		{
			shell_exit(user_input);
			is_comment(user_input);
			is_colon(user_input);

			if (strstr(user_input, "setenv") || strstr(user_input, "unsetenv"))
			{
				args = shell_split_line(user_input);
				set_unset(args);
			}
			else
			{
				args = shell_split_line(user_input);
				status = shell_launch(user_input, args);
			}

			free_mem(user_input, args);
		}
		else
			break;
	} while (status == 0);

	if (status == 1)
		return (127);

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
 *  is_colon - handles the ; character
 * @line: The line of input from the user
 * Return: void
 */
void is_colon(char *line)
{
	int i = 0;
	char **cmd;

	if (strchr(line, ';') == NULL)
	{
		return;
	}

	cmd = command(line);
	while (cmd[i] != NULL)
	{
		system(cmd[i]);
		i++;
	}
	free(cmd);
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
