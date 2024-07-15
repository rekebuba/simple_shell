#include "main.h"

/**
 * array_len - determine the length of array using a simple loop.
 * @args: array of strings
 * Return: length
 */
int array_len(char **args)
{
	int arg_count = 0;

	while (args[arg_count])
	{
		arg_count++;
	}

	return (0);
}

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

	if (str)
	{
		next_token = str;
	}
	if (next_token == NULL)
	{
		return (NULL);
	}
	while (*next_token != '\0' && strchr(delim, *next_token))
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

/**
 * _strcmp - compare two strings
 * @str1: string 1
 * @str2: string 2
 * Return: int
 */
int _strcmp(const char *str1, const char *str2)
{
	while (*str1 && (*str1 == *str2))
	{
		str1++;
		str2++;
	}

	return (*(unsigned char *)str1 - *(unsigned char *)str2);
}

/**
 * _strcspn - _strcspn
 * @str1: string 1
 * @str2: string 2
 * Return: size_t
 */
size_t _strcspn(const char *str1, const char *str2)
{
	const char *p1, *p2;
	size_t count = 0;

	for (p1 = str1; *p1 != '\0'; p1++)
	{
		for (p2 = str2; *p2 != '\0'; p2++)
		{
			if (*p1 == *p2)
				return (count);
		}

		count++;
	}

	return (count);
}

/**
 * tokenize - tokenize the string by semicolon
 * @arg: the string passed
 * @delimeter: delimeter passed as an argument
 * Return: char**
 */
char **tokenize(char *arg, char *delimeter)
{
	char **tokens = malloc(BUFFER * sizeof(char *));
	char *token;
	int index = 0;

	if (!tokens)
	{
		dprintf(2, "error allocating memory");
		exit(EXIT_FAILURE);
	}
	token = _strtok(arg, delimeter);
	while (token)
	{
		tokens[index] = token;
		index++;
		token = _strtok(NULL, delimeter);
	}
	tokens[index] = NULL;

	return (tokens);
}
