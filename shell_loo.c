#include "main.h"

/**
 * command - command
 * @arg: the string passed
 * Return: char**
 */
char **command(char *arg)
{
	char **tokens = malloc(BUFFER * sizeof(char *));
	char *token;
	int index = 0;

	if (!tokens)
	{
		dprintf(2, "error allocating memory");
		exit(EXIT_FAILURE);
	}
	token = _strtok(arg, ";");
	while (token != NULL)
	{
		tokens[index] = token;
		index++;
		token = _strtok(NULL, ";");
	}
	tokens[index] = NULL;
	return (tokens);
}
