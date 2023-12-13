#include "main.h"

/**
 * is_comment - it checks the # character
 * @line: the string passed
 * Return: void
 */
void is_comment(char *line)
{
	int i;
	removeWhiteSpace(line);
	for (i = 0; line[i]; i++)
	{
		if (line[i] == '#')
		{
			line[i] = '\0';
			removeWhiteSpace(line);
		}
	}
}
