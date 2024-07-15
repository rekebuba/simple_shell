#include "main.h"

/**
 * logical_ope - handles the && || logical operator
 * @user_input: The line of input from the user
 * @head: head of a single linked list that contains aliases
 * Return: status
 */
int logical_ope(struct Node **head, char *user_input)
{
	int i = 0;
	char **command;
	int status = 0;
	char **args;
	char *found;

	char *first_occurrence = user_input;
	char *ptr = strdup(user_input);

	command = tokenize(ptr, "&&||");
	while (command[i])
	{
		found = strpbrk(first_occurrence, "&&||");
		args = shell_split_line(head, command[i]);
		status = shell_launch(head, user_input, args, status);
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

/**
 * is_colon - handles the ; character
 * @head: head of a single linked list that contains aliases
 * @user_input: The line of input from the user
 * Return: status
 */
int is_colon(struct Node **head, char *user_input)
{
	int i = 0;
	char **command;
	char **args;
	int status = 0;

	char *ptr = strdup(user_input);

	command = tokenize(ptr, ";");
	while (command[i])
	{
		args = shell_split_line(head, command[i]);
		status = shell_launch(head, user_input, args, status);
		free(ptr);
		free(args);
		i++;
	}
	free(command);
	return (status);
}

/**
 * set_unset_env - This function sets or un_sets environment variables
 *
 * @args: The arguments passed to the function
 *
 * Return: void
 */
void set_unset_env(char **args)
{
	int i;

	if (args[1] == NULL)
		return;

	for (i = 0; args[i]; i++)
	{
		if (_strcmp(args[i], "setenv") == 0)
		{
			if (args[i + 2] && setenv(args[i + 1], args[i + 2], 1) != 0)
			{
				dprintf(2, "Failed to set environment variable\n");
			}
		}
		else if (_strcmp(args[i], "unsetenv") == 0)
		{
			if (unsetenv(args[i + 1]) != 0)
			{
				dprintf(2, "Failed to unset environment variable\n");
			}
		}
		else if (array_len(args) == 1 && _strcmp(args[i], "env") == 0)
		{
			system(args[i]);
		}
	}
}
