#include "main.h"

/**
 * main -
 *
 * @argc
 * @argv
 * Return: int
 */
int main(int argc, char *argv)
{
	shell_loop();
}

void shell_loop(void)
{
	char *line;
	char **args;
	int status;

	do
	{
		printf("$ ");
		line = shell_read_line();
		args = shell_split_line(line);
		status = shell_execute(args);

		free(line);
		free(args);
	} while (status);
}
/**
 * shell_split_line -
 *
 * @line:
 * Return: char**
 */
char **shell_split_line(char *line)
{
	int buffer_size = BUFFER;
	int index = 0;
	char **tokens = malloc(buffer_size * sizeof(char *));
	char *token;

	if (!tokens)
	{
		fprintf(stderr, "ERROR: failed to allocate memory\n");
		exit(EXIT_FAILURE);
	}

	token = _strtok(line, TOK_DELIM);
	while (token != NULL)
	{
		tokens[index] = token;
		index++;

		if (index >= BUFFER)
		{
			buffer_size += BUFFER;
			tokens = realloc(tokens, buffer_size * sizeof(char *));
			if (!tokens)
			{

				fprintf(stderr, "ERROR: failed to allocate memory\n");
				exit(EXIT_FAILURE);
			}
		}
		token = _strtok(NULL, TOK_DELIM);
	}
	tokens[index] = NULL;
	return (tokens);
}

/**
 * shell_read_line
 *
 * Return: char*
 */
char *shell_read_line(void)
{
	char *buffer = malloc(BUFFER * sizeof(char));
	int index = 0;
	int buffer_size = BUFFER;
	int c;

	if (!buffer)
	{
		fprintf(stderr, "ERROR: failed to allocate memory\n");
		exit(EXIT_FAILURE);
	}
	while (true)
	{
		/*read character by character*/
		c = getchar();
		if (c == EOF || c == '\n')
		{
			buffer[index] = '\0';
			return (buffer);
		}
		else
		{
			buffer[index] = c;
		}
		index++;
		/* if we have exceeded the buffer, reallocate*/
		if (index >= buffer_size)
		{
			buffer_size += BUFFER;
			buffer = realloc(BUFFER, buffer_size);
			if (!buffer)
			{
				fprintf(stderr, "ERROR: failed to allocate memory\n");
				exit(EXIT_FAILURE);
			}
		}
	}
}

/**
 * _strtok -
 *
 * @str
 * @delimiter
 * Return: char*
 */
char *_strtok(char *str, const char *delimiter)
{
	static char *buffer = NULL;
	if (str != NULL)
	{
		buffer = str;
	}
	if (buffer == NULL)
	{
		return NULL;
	}
	char *token = buffer;
	buffer += strcspn(buffer, delimiter);
	if (*buffer != '\0')
	{
		*buffer = '\0';
		buffer++;
	}
	else
	{
		buffer = NULL;
	}
	return token;
}
