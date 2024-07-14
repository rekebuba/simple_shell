#include "main.h"

/**
 * shell_split_line - it split the line by specifed delimeter
 * @line: the argument passed
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
		perror("ERROR: failed to allocate memory\n");
		exit(EXIT_FAILURE);
	}

	token = _strtok(line, TOK_DELIM);
	while (token)
	{
		tokens[index] = token;
		index++;

		if (index >= BUFFER)
		{
			buffer_size += BUFFER;
			tokens = realloc(tokens, buffer_size * sizeof(char *));
			if (!tokens)
			{
				perror("ERROR: failed to allocate memory\n");
				exit(EXIT_FAILURE);
			}
		}
		token = _strtok(NULL, TOK_DELIM);
	}
	tokens[index] = NULL;

	valid_input(tokens);

	return (tokens);
}

/**
 * valid_input - modify user input either from env or alias
 * @args: users input in argument form
 * Returns: void
 */
void valid_input(char **args)
{
	int index = 0;
	char *env;

	while (args[index])
	{
		if (strcmp(args[0], "alias") != 0)
			args[index] = assign_value(args[index]);

		if (*args[index] == '$' && getenv(args[index] + 1))
		{
			env = getenv(args[index] + 1);
			args[index] = env;
		}
		else if (*args[index] == '$' && !getenv(args[index] + 1))
		{
			if (args[index][1] != '\0' &&
				_strcmp(args[index], "$$") != 0 && _strcmp(args[index], "$?") != 0)
			{
				if (index == 0 && args[index + 1] == NULL)
					args[index] = NULL;
				else
					args[index] = args[index + 1] == NULL ? "" : args[index + 1];
			}
		}
		index++;
	}
}
