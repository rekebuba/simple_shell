#include "main.h"

/**
 * main - the main program
 * @argc: number of argument count
 * @argv: the argument passed
 * Return: int
 */
int main(void)
{
	char *line;
	char **args;
	int status = 0, i;
	char **cmd;

	signal(SIGINT, _signal);
	do
	{
		line = read_line();
		if (line != NULL)
		{
			is_comment(line);
			if (strchr(line, ';') != NULL)
			{
				cmd = command(line);
				i = 0;
				while (cmd[i] != NULL)
				{
					system(cmd[i]);
					i++;
				}
				free(cmd);
			}
			else
			{
				args = shell_split_line(line);
				if (args[0] != NULL)
				{
					status = shell_launch(args);
				}
				free(args);
			}
			free(line);
		}
		else
		{
			break;
		}
	} while (status == 0);

	if (status == 1)
		return (127);

	return (status);
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
