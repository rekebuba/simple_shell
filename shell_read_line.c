#include "main.h"

/**
 * shell_read_line - it reads a line imputed bu the user
 *
 * Return: char*
 */
char *shell_read_line(void)
{
	char *buffer = malloc(BUFFER * sizeof(char));
	int index = 0;
	int buffer_size = BUFFER;
	int c;
	int i;
	int len;

	if (!buffer)
	{
		perror("ERROR: failed to allocate memory\n");
		exit(EXIT_FAILURE);
	}

	while (true)
	{
		/*read character by character*/
		c = getchar();
		if (c == EOF)
			exit(EXIT_SUCCESS);
		if (c == EOF || c == '\n')
		{
			buffer[index] = '\0';
			buffer = removeWhiteSpace(buffer);
			len = strlen(buffer);
			for (i = 0; i < len; i++)
			{
				if (buffer[i] == '#')
				{
					buffer[i] = '\0';
					buffer = removeWhiteSpace(buffer);
					return (buffer);
				}
			}
			return (buffer);
		}
		else
		{
			buffer[index] = c;
		}
		index++;
		/* if we have exceeded the buffer, reallocate */
		if (index >= buffer_size)
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
