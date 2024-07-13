#include "main.h"

/**
 * read_line - read a line from stdin
 *
 * Return: void
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

	read = getline(&line, &len, stdin);

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
	if (strstr(line, " #") != NULL || *line == '#')
	{
		line[_strcspn(line, "#")] = '\0';
	}
}
