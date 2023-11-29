#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define BUFFER 1024

/**
 * @brief
 *
 * @param argc
 * @param argv
 * @return int
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
 * @brief
 *
 * @return char*
 */
char *shell_read_line(void)
{
	char *buffer = malloc(BUFFER * sizeof(char));
	int index = 0;
	int buffer_size = BUFFER;
	int c;

	if (!buffer)
	{
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
				exit(EXIT_FAILURE);
			}
		}
	}
}

/**
 * @brief
 *
 * @return int
 */
int getchar(void)
{
}