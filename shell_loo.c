#include "main.h"

/*
 * shell_loop - uses to prompt the user
 * @void: void
 * Return: int
 */
int shell_loop(void)
{
	ssize_t read;
	char *line = NULL;
	char **args, **cmd;
	int status, i;
	size_t len = 0;

	do {
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
			break;
		}
		line[strcspn(line, "\n")] = '\0';
		is_comment(line);
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
		else
		{
			args = shell_split_line(line);
			status = shell_launch(args);
			free(args);
		}
	} while (status == 0);
	free(line);
	if (status == 1)
		return (127);
	return (status);
}

/**
 * command - command
 * @arg: the string passed
 * Return: char**
 */
char **command(char *arg)
{
	char **tokens = malloc(BUFFER * sizeof(char *));
	char *token;
	int index = 0;

	if (!tokens)
	{
		dprintf(2, "error allocating memory");
		exit(EXIT_FAILURE);
	}
	token = _strtok(arg, ";");
	while (token != NULL)
	{
		tokens[index] = token;
		index++;
		token = _strtok(NULL, ";");
	}
	tokens[index] = NULL;
	return (tokens);
}
