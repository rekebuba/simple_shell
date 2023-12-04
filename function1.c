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

	do {
		dprintf(1, "$ ");
		line = shell_read_line();
		args = shell_split_line(line);
		status = shell_launch(args);

		free(line);
		free(args);
	} while (status);
}

/**
 * shell_split_line - it split the line by specifed delimeter
 * @line: the argument passed
 * Return: char**
 */
char **shell_split_line(char *line)
{
	int buffer_size = BUFFER;
	int index = 0;
	char **tokens = malloc(buffer_size * sizeof(char *));
	char *token;

	if (!tokens)
	{
		perror("ERROR: failed to allocate memory\n");
		exit(EXIT_FAILURE);
	}

	token = _strtok(line, TOK_DELIM);
	while (token != NULL)
	{
		tokens[index] = token;
		index++;

		if (index >= BUFFER)
		{
			buffer_size += BUFFER;
			tokens = realloc(tokens, buffer_size * sizeof(char *));
			if (!tokens)
			{

				perror("ERROR: failed to allocate memory\n");
				exit(EXIT_FAILURE);
			}
		}
		token = _strtok(NULL, TOK_DELIM);
	}
	tokens[index] = NULL;

	return (tokens);
}
