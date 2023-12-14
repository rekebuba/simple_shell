#include "main.h"

/**
 * main - the main program
 * @argc: number of argument count
 * @argv: the argument passed
 * Return: int
 */
int main(int argc, char **argv)
{
	ssize_t read;
	char *line = NULL;
	char **args;
	int status;
	size_t len = 0;
	(void)argc;
	(void)argv;
	signal(SIGINT, _signal);
	do {
		if (isatty(STDIN_FILENO))
		{
			printf("$ ");
			fflush(stdout);
		}
		read = get_line(&line, &len, stdin);
		if (read == -1)
		{
			if (isatty(STDIN_FILENO))
				printf("\n");
			break;
		}
		is_comment(line);
		if (_strcmp(line, "\0") != 0)
		{
			args = shell_split_line(line);
			status = shell_launch(args);
			free(args);
		}
		free(line);
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
