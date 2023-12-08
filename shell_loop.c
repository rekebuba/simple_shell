#include "main.h"

/*
 * shell_loop - uses to prompt the user
 * Return: void
 */
void shell_loop(void)
{
	char *line;
	char **args;
	int status;
	while (true)
	{
		/* printf("$ ");
		fflush(stdout); */
		line = shell_read_line();
		
		args = shell_split_line(line);
		status = shell_launch(args);

		free(line);
		free(args);
	}
	(void)status;
}
