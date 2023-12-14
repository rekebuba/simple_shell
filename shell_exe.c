#include "main.h"

/**
 * shell_execute - it executes the command entered
 * @args: the argument passed
 * Return: int
 */
int shell_execute(char **args)
{
	pid_t pid;
	int status = 0;
	static int count = 1;

	pid = fork();

	if (pid == 0)
	{
		/* were in the chilled processor */
		if (execvp(args[0], args) == -1)
		{
			dprintf(2, "./hsh: %d: %s: not found\n", count, args[0]);
			count++;
			exit(EXIT_FAILURE);
		}
	}
	else if (pid < 0)
	{
		/* failed to fork */
		perror("failed to fork\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		/* were in the parent processor */
		do {
			waitpid(pid, &status, WUNTRACED);
			count++;
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	if (!isatty(STDIN_FILENO))
	{
		return (WEXITSTATUS(status));
	}

	return (0);
}
