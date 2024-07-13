#include "main.h"

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
		do {
			if (_strcmp(args[0], "echo") == 0 && _strcmp(args[1], "$?") == 0)
				dprintf(1, "%d\n", prev_status);
			else if (_strcmp(args[0], "echo") == 0 && _strcmp(args[1], "$$") == 0)
				dprintf(1, "%d\n", getpid());

			waitpid(pid, &status, WUNTRACED);
			count++;
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	return (WEXITSTATUS(status) == 1 ? 127 : WEXITSTATUS(status));
}
