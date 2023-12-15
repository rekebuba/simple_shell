#include "main.h"

/**
 * _strtok - used to tokenize a string besed on specified delimeter
 *
 * @str: the string that needs to be tokenize
 * @delim: delimiters
 * Return: char*
 */
char *_strtok(char *str, const char *delim)
{
	static char *next_token;
	char *token;

	if (str != NULL)
	{
		next_token = str;
	}
	if (next_token == NULL)
	{
		return (NULL);
	}
	while (*next_token != '\0' && strchr(delim, *next_token) != NULL)
	{
		next_token++;
	}
	if (*next_token == '\0')
	{
		return (NULL);
	}
	token = next_token;
	while (*next_token != '\0' && strchr(delim, *next_token) == NULL)
	{
		next_token++;
	}
	if (*next_token != '\0')
	{
		*next_token = '\0';
		next_token++;
	}

	return (token);
}
