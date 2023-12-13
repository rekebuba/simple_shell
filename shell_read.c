#include "main.h"

/**
 * shell_read_line - it reads a line imputed bu the user
 *
 * Return: char*
 */
char *shell_read_line(void)
{
	char *buffer = malloc(BUFFER * sizeof(char));
	int character, index = 0;
	int i;

	if (!buffer)
	{
		perror("ERROR: Failed to allocate memory\n");
		exit(EXIT_FAILURE);
	}
	while ((character = getchar()) != EOF && character != '\n')
	{
		buffer[index++] = character;
	}
	if (character == EOF)
	{
		if (isatty(STDIN_FILENO))
		{
			printf("\n");
			fflush(stdout);
		}
		exit(1);
	}
	buffer[index] = '\0';
	removeWhiteSpace(buffer);

	for (i = 0; buffer[i]; i++)
	{
		if (buffer[i] == '#')
		{
			buffer[i] = '\0';
			removeWhiteSpace(buffer);
			return (buffer);
		}
	}
	return (buffer);
}
