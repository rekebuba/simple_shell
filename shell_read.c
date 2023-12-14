#include "main.h"

/**
 * is_comment - it checks the # character
 * @line: the string passed
 * Return: void
 */
void is_comment(char *line)
{
	int i;
	char **cmd;
	line[strcspn(line, "\n")] = '\0';
	removeWhiteSpace(line);
	for (i = 0; line[i]; i++)
	{
		if (line[i] == '#')
		{
			line[i] = '\0';
			removeWhiteSpace(line);
		}
	}
	if (char_in_str(line, ';') != NULL)
	{
		cmd = command(line);
		i = 0;
		while (cmd[i] != NULL)
		{
			_system(cmd[i]);
			i++;
		}
		free(cmd);
	}
}
