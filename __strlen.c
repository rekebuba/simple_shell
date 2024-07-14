#include "main.h"

/**
 * _strlen - checks the length of a string
 * @str: the string passed
 * Return: size_t
 */
size_t _strlen(const char *str)
{
	const char *s = str;

	while (*s)
	{
		s++;
	}
	return (s - str);
}

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
