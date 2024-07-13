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

	if (*line_ptr == NULL || *n == 0)
	{
		*n = 16;
		*line_ptr = malloc(*n);
		if (*line_ptr == NULL)
			return (-1);
	}
	line = *line_ptr;
	while ((c = fgetc(stream)) != EOF)
	{
		if (len + 1 >= *n)
		{
			*n *= 2;
			temp = realloc(line, *n);
			if (temp == NULL)
			{
				free(line);
				return (-1);
			}
			line = temp;
			*line_ptr = line;
		}
		line[len++] = (char)c;
		if (c == '\n')
			break;
	}
	if (ferror(stream))
		return (-1);
	if (len == 0 && c == EOF)
		return (-1);

	line[len] = '\0';
	return (len);
}
