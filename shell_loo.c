#include "main.h"

/*
 * shell_loop - uses to prompt the user
 * @void: void
 * Return: void
 */
void shell_loop(void)
{
	char *line;
	char **args;
	char **cmd;
	int status;
	int i;

	do {
		if (isatty(STDIN_FILENO))
		{
			printf("$ ");
			fflush(stdout);
		}
		line = shell_read_line();
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
		free(line);
	} while (status);
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
