#include "main.h"

/**
 * tok_colon - tokenize the string by semicolon
 * @arg: the string passed
 * Return: char**
 */
char **tok_colon(char *arg)
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
