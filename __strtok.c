#include "main.h"

/**
 * _strtok - used to tokenize a string besed on specified delimete
 *
 * @str: the string that needs to be tokenize
 * @delimiter: delimiters
 * Return: char*
 */
char *_strtok(char *str, const char *delimiter)
{
	static char *buffer = NULL;
	char *token;

	if (str != NULL)
	{
		buffer = str;
	}

	if (buffer == NULL)
	{
		return (NULL);
	}

	token = buffer;
	buffer += _strcspn(buffer, delimiter);
	if (*buffer != '\0')
	{
		*buffer = '\0';
		buffer++;
	}
	else
	{
		buffer = NULL;
	}

	return (token);
}

