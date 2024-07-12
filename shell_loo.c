#include "main.h"

/**
 * tok_colon - tokenize the string by semicolon
 * @arg: the string passed
 * Return: char**
 */
char **tok_colon(char *arg)
{
	char **tokens = malloc(BUFFER * sizeof(char *));
	char *token;
	int index = 0;

	if (!tokens)
	{
		dprintf(2, "error allocating memory");
		exit(EXIT_FAILURE);
	}
	token = _strtok(arg, ";&&||");
	while (token != NULL)
	{
		tokens[index] = token;
		index++;
		token = _strtok(NULL, ";&&||");
	}
	tokens[index] = NULL;
	return (tokens);
}

/**
 * logical_ope - handles the && || logical operator
 * @user_input: The line of input from the user
 * Return: status
 */
int logical_ope(char *user_input)
{
	int i = 0;
	char **command;
	int status = 0;
	char **args;
	char *found;

	char *first_occurrence = user_input;
	char *ptr = strdup(user_input);

	command = tok_colon(ptr);
	while (command[i] != NULL)
	{
		found = strpbrk(first_occurrence, "&&||");
		args = shell_split_line(command[i]);
		status = shell_launch(user_input, args);
		if (found && ((*found == '&' && status != 0) ||
					  (*found == '|' && status == 0)))
		{
			free(args);
			break;
		}
		else if (found)
		{
			first_occurrence = found + 2;
		}
		free(args);
		i++;
	}
	free(command);
	free(ptr);
	return (status);
}
