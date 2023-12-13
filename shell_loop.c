#include "main.h"

/*
 * shell_loop - uses to prompt the user
 * Return: void
 */
void shell_loop(void)
{
	char *line;
	char **args;
	char **cmd;
	int status;
	int i;
	while (true)
	{
		printf("$ ");
		fflush(stdout);
		line = shell_read_line();
		if (strchr(line, ';') != NULL)
		{
			cmd = command(line);
			i = 0;
			while (cmd[i] != NULL)
			{
				system(cmd[i]);
				i++;
			}
			free(cmd);
			free(line);
		}
		else
		{
			args = shell_split_line(line);
			status = shell_launch(args);
			free(line);
			free(args);
		}
	}
	(void)status;
}

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
