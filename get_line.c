#include "main.h"

/**
 * get_line - Get the line object
 * @line_ptr: double pointer
 * @n: unsigned int
 * @stream: file stream
 * Return: ssize_t
 */
ssize_t get_line(char **line_ptr, size_t *n, FILE *stream)
{
	size_t len = 0;
	int c;
	char *temp, *line = NULL;

	if (line_ptr == NULL || n == NULL)
		return (-1);
	do {
		c = fgetc(stream);
		if (c == EOF)
			break;
		if (len == 0)
		{
			*n = 16;
			line = malloc(*n);
			if (line == NULL)
				return (-1);
		}
		line[len++] = c;
		if (c == '\n')
			break;
		if (len == *n)
		{
			*n *= 2;
			temp = realloc(line, *n);
			if (temp == NULL)
			{
				free(line);
				return (-1);
			}
			line = temp;
		}
	} while (1);
	if (len == 0)
	{
		free(line);
		return (-1);
	}
	line[len] = '\0';
	*line_ptr = line;
	return (len);
}
