#include "main.h"

/**
 * read_line - read a line from stdin
 * @line: shell line
 * Return: void
 */
char *read_line(char *line)
{
	ssize_t read;
	size_t len = 0;

	if (isatty(STDIN_FILENO))
	{
		printf("$ ");
		fflush(stdout);
	}

	read = get_line(&line, &len, stdin);

	if (read == -1)
	{
		if (isatty(STDIN_FILENO))
			printf("\n");
		free(line);
		line = NULL;
	}
	else
	{
		line[_strcspn(line, "\n")] = '\0';
	}

	return (line);
}

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

/**
 * shell_split_line - it split the user_input by specifed delimeter
 * @head: head of a single linked list that contains aliases
 * @user_input: the argument passed
 * Return: char**
 */
char **shell_split_line(struct Node **head, char *user_input)
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

	token = _strtok(user_input, TOK_DELIM);
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

	valid_input(head, tokens);

	return (tokens);
}

/**
 * valid_input - modify user input either from env or alias
 * @head: head of a single linked list that contains aliases
 * @args: users input in argument form
 * Returns: void
 */
void valid_input(struct Node **head, char **args)
{
	int index = 0;
	char *env;

	while (args[index])
	{
		if (strcmp(args[0], "alias") != 0)
			args[index] = assign_value(head, args[index]);

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

/**
 * assign_value - assign value to the shell prompt if it has alias
 * @head: head of a single linked list that contains aliases
 * @key: prompt to check
 * Return: modified value
 */
char *assign_value(struct Node **head, char *key)
{
	struct Node *current;
	bool status = false;

	if (head == NULL)
		return (key);

	current = *head;
	while (current)
	{
		if (strcmp(current->key, key) == 0)
		{
			status = true;
			strcpy(key, current->value);
		}
		current = current->next;
	}

	if (status)
	{
		return (assign_value(head, key));
	}
	return (key);
}
