#include "main.h"

/**
 * shell_launch - all the builtin are executed inside this func
 * @head: head of a single linked list that contains aliases
 * @user_input: users input
 * @args: the argument passed
 * @prev_status: return the previous status of the child process
 * Return: int
 */
int shell_launch(struct Node **head,
				 char *user_input, char **args, int prev_status)
{
	int i = 0;
	char *built_in_str[] = {"cd", "alias"};

	int (*builtin_function[])(struct Node **, char **) = {&shell_cd, shell_alias};
	int number_of_builtin = sizeof(built_in_str) / sizeof(char *);

	if (args[0] == NULL)
	{
		return (0);
	}

	for (i = 0; i < number_of_builtin; i++)
	{
		if (_strcmp(args[0], built_in_str[i]) == 0)
		{
			return (builtin_function[i](head, args));
		}
	}
	/* if no argument is found */
	return (shell_execute(user_input, args, prev_status));
}

/**
 * shell_execute - it executes the command entered
 * @user_input: users input
 * @args: the argument passed
 * @prev_status: return the previous status of the child process
 * Return: int
 */
int shell_execute(char *user_input, char **args, int prev_status)
{
	pid_t pid;
	int status = 0;
	static int count = 1;

	pid = fork();
	if (pid == 0) /* were in the chilled processor */
	{
		if (_strcmp(args[0], "echo") == 0 && ((_strcmp(args[1], "$?") == 0) ||
											  _strcmp(args[1], "$$") == 0))
		{
			free_mem(user_input, args);
			exit(EXIT_SUCCESS);
		}
		else if (execvp(args[0], args) == -1)
		{
			dprintf(2, "./hsh: %d: %s: not found\n", count, args[0]);
			count++;
			free_mem(user_input, args);
			exit(EXIT_FAILURE);
		}
	}
	else if (pid < 0) /* failed to fork */
	{
		perror("failed to fork\n");
		free_mem(user_input, args);
		exit(EXIT_FAILURE);
	}
	else /* were in the parent processor */
	{
		if (_strcmp(args[0], "echo") == 0 && _strcmp(args[1], "$?") == 0)
			dprintf(1, "%d\n", prev_status);
		else if (_strcmp(args[0], "echo") == 0 && _strcmp(args[1], "$$") == 0)
			dprintf(1, "%d\n", getpid());
		do {
			waitpid(pid, &status, WUNTRACED);
			count++;
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	return (WEXITSTATUS(status) == 1 ? 127 : WEXITSTATUS(status));
}
