#include "main.h"

/**
 * shell_read_line - it reads a line imputed bu the user
 *
 * Return: char*
 */
char *shell_read_line(void)
{
	char *buffer = malloc(BUFFER * sizeof(char));
	int buffer_size = BUFFER;
	int character, i, len, index = 0;
	if (!buffer)
	{
		perror("ERROR: failed to allocate memory\n");
		exit(EXIT_FAILURE);
	}
	while (true)
	{
		character = getchar();
		if (character == EOF)
			exit(EXIT_SUCCESS);
		if (character == EOF || character == '\n')
		{
			buffer[index] = '\0';
			removeWhiteSpace(buffer);
			len = _strlen(buffer);
			for (i = 0; i < len; i++)
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
		else
			buffer[index] = character;
		index++;
		if (index >= buffer_size)/* if we have exceeded the buffer, reallocate */
		{
			buffer_size += BUFFER;
			buffer = realloc(buffer, buffer_size);
			if (!buffer)
			{
				perror("ERROR: failed to allocate memory\n");
				exit(EXIT_FAILURE);
			}
		}
	}
}
