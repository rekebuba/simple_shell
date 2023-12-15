#include "main.h"

/**
 * main - the main program
 * Return: void
 */
int main(void)
{
	char *line;
	char **args;
	int status = 0;

	signal(SIGINT, _signal);
	do {
		line = read_line();
		if (line != NULL)
		{
			if (strstr(line, "exit") != NULL)
				shell_exit(line);
			else
			{
				is_comment(line);
				if (strchr(line, ';') != NULL)
					is_colon(line);
				else
				{
					if (strstr(line, "setenv") != NULL || strstr(line, "unsetenv") != NULL)
					{
						args = shell_split_line(line);
						set_unset(args);
					}
					else
					{
					args = shell_split_line(line);
					if (args[0] != NULL)
					status = shell_launch(args);
					}
					free(args);
				}
				free(line);
			}
		}
		else
			break;
	} while (status == 0);
	if (status == 1)
		return (127);
	return (status);
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
			if (setenv(args[i + 1], args[i + 2], 1) != 0)
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
		else if (_strcmp(args[i], "env") == 0)
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
