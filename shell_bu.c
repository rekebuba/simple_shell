#include "main.h"

/**
 * shell_cd - the cd command
 *
 * @args: the argument passed
 * Return: int
 */
int shell_cd(char **args)
{
	char *home_dir;

	if (args[1] == NULL || _strcmp(args[1], "-") == 0)
	{
		home_dir = getenv("HOME");
		if (home_dir != NULL)
		{
			if (chdir(home_dir) != 0)
			{
				dprintf(2, "./hsh: 1: cd: can't cd to %s\n", args[1]);
			}
		}
	}
	else
	{
		if (chdir(args[1]) != 0)
		{
			dprintf(2, "./hsh: 1: cd: can't cd to %s\n", args[1]);
		}
	}

	return (0);
}

/**
 * shell_exit - the exit command
 *
 * @args: the argument passed
 * Return: int
 */
int shell_exit(char **args)
{
	int i;
	int len;

	if (args[1] != NULL)
	{
		len = _strlen(args[1]);
		for (i = 0; i < len; i++)
		{
			if (!isdigit(args[1][i]))
			{
				dprintf(2, "./hsh: 1: exit: Illegal number: %s\n", args[1]);
				exit(2);
			}
		}
		exit(_atoi(args[1]));
	}
	exit(EXIT_SUCCESS);
}

/**
 * _setenv - sets an environment variable
 * @args: the argument passed
 *
 * Returns: 0 on success, -1 on failure
 */
int _setenv(char **args)
{
	if (setenv(args[1], args[2], 1))
	{
		dprintf(2, "failed to set variable.\n");
		return (-1);
	}
	return (0);
}
/**
 * _unsetenv - un_sets an environment variable
 * @args: the argument passed
 *
 * Returns: 0 on success, -1 on failure
 */
int _unsetenv(char **args)
{
	if (unsetenv(args[1]) != 0)
	{
		dprintf(2, "failed to unset variable.\n");
		return (-1);
	}
	return (0);
}

/**
 * shell_launch - all the builtin are executed inside this func
 *
 * @args: the argument passed
 * Return: int
 */
int shell_launch(char **args)
{
	int i;
	char *built_in_str[] = {"cd", "exit", "setenv", "unsetenv"};

	int (*builtin_function[])(char **) = {&shell_cd, &shell_exit, &_setenv, &_unsetenv};
	int number_of_builtin = sizeof(built_in_str) / sizeof(char *);

	for (i = 0; i < number_of_builtin; i++)
	{
		if (_strcmp(args[0], built_in_str[i]) == 0)
		{
			return (builtin_function[i](args));
		}
	}
	/* if no argument is found */
	return (shell_execute(args));
}
