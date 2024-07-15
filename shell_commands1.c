#include "main.h"

/**
 * shell_cd - the cd command
 * @head: head of a single linked list that contains aliases
 * @args: the argument passed
 * Return: int
 */
int shell_cd(struct Node **head, char **args)
{
	char *home_dir = getenv("HOME") == NULL ? getenv("PWD") : getenv("HOME");
	char *old_pwd = getenv("OLDPWD") == NULL ? getenv("PWD") : getenv("OLDPWD");
	char cwd[1024];

	(void)head;

	/* Handle "cd" or "cd -" */
	if (args[1] == NULL || strcmp(args[1], "-") == 0)
	{
		if (args[1] == NULL)
		{
			chdir(home_dir);
		}
		else if (strcmp(args[1], "-") == 0)
		{
			if (chdir(old_pwd) == 0)
			{
				dprintf(1, "%s\n", old_pwd);
			}
		}
	}
	else
	{
		if (chdir(args[1]) != 0)
		{
			dprintf(2, "./hsh: 1: cd: can't cd to %s\n", args[1]);
			return (1);
		}
	}
	/* Update OLDPWD and PWD environment variables */
	setenv("OLDPWD", getenv("PWD"), 1);
	if (getcwd(cwd, sizeof(cwd)))
	{
		setenv("PWD", cwd, 1);
	}

	return (0);
}

/**
 * shell_exit - the exit command
 * @head: head of a single linked list that contains aliases
 * @line: the string passed
 * @prev_status: return the previous status of the child process
 * Return: void
 */
void shell_exit(struct Node **head, char *line, int prev_status)
{
	int i = 0, l;
	char *result = NULL;

	if (strstr(line, "exit") == NULL)
	{
		return;
	}

	result = _strtok(line, " ");
	result = _strtok(NULL, " ");
	if (result)
	{
		for (i = 0; result[i]; i++)
		{
			if (!isdigit(result[i]))
			{
				dprintf(2, "./hsh: 1: exit: Illegal number: %s\n", result);
				if (!isatty(STDIN_FILENO))
				{
					free(line);
					freeList(*head);
					exit(2);
				}
				return;
			}
		}
		l = atoi(result);
		freeList(*head);
		free(line);
		exit(l);
	}
	freeList(*head);
	free(line);
	exit(prev_status);
}

/**
 * is_comment - it checks the # character
 * @line: the string passed
 * Return: void
 */
void is_comment(char *line)
{
	if (strstr(line, " #") || *line == '#')
	{
		line[_strcspn(line, "#")] = '\0';
	}
}
