#include "main.h"
/**
 * removeWhiteSpace - it removes unnecessary whitespace
 * @str: the string that needs to be modified
 * Return: void
 */
void removeWhiteSpace(char *str)
{
	char *p1 = str; /* pointer to iterate through the input string */
	char *p2 = str; /* pointer to write the non-space characters to */
	bool space = false;

	while (_space(*p1))
	{
		p1++;
	}

	while (*p1 != '\0')
	{
		if (_space(*p1))
		{
			if (!space)
			{
				*p2 = *p1;
				p2++;
				space = true;
			}
		} 
		else
		{
			*p2 = *p1;
			p2++;
			space = false;
		}
		p1++;
	}

	if (_space(*(p2 - 1)))
	{
		*(p2 - 1) = '\0';
	}

	*p2 = '\0';
}

/**
 * _space - check if a character is a space 
 * 
 * @c: the character passed
 * Return: int
 */
int _space(int c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f' || c == '\v');
}
