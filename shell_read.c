#include "main.h"

/**
 * read_line
 *
 * Return: char*
 */
char *read_line()
{
	char *line = NULL;
	ssize_t read;
	size_t len = 0;

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
		free(line);
		line = NULL;
	}
	else
	{
		line[_strcspn(line, "\n")] = '\0';
	}

	return (line);
}

/**
 * is_comment - it checks the # character
 * @line: the string passed
 * Return: void
 */
void is_comment(char *line)
{
	int i;
	char **cmd;
	if (strchr(line, '#') != NULL)
	{
		line[_strcspn(line, "#")] = '\0';
	}
	else if (strchr(line, ';') != NULL)
	{
		cmd = command(line);
		i = 0;
		while (cmd[i] != NULL)
		{
			_system(cmd[i]);
			i++;
		}
		free(cmd);
	}
}
