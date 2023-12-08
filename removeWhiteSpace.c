#include "main.h"
/**
 * removeWhiteSpace - it removes unnecessary whitespace
 * @str: the string that needs to be modified
 * Return: void
 */
char *removeWhiteSpace(char *str)
{
	char *p1 = str;		/* pointer to iterate through the input string */
	/* pointer to write the non-space characters to */
	char *new = malloc(BUFFER * sizeof(char));
	int index = 0;
	bool space = false; /* flag to track consecutive spaces */

	while (isspace(*p1))
	{
		p1++;
	}

	while (*p1 != '\0')
	{
		if (isspace(*p1))
		{
			if (!space)
			{
				new[index++] = *p1;
				space = true;
			}
		}
		else
		{
			new[index++] = *p1;
			space = false;
		}
		p1++;
	}

	if (isspace(new[index - 1]))
	{
		new[index - 1] = '\0';
	}

	new[index] = '\0'; /* Null-terminate the modified string */
	return (new);
}
