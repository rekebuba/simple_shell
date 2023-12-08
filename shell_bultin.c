#include "main.h"

/**
 * built_in_str- creating an array of builtin commands

 */
char *built_in_str[] = {"cd", "exit"};

/**
 * builtin_function - if the first argument is found for builtin commands
 * it calls the function that is needed
 *
 */
int (*builtin_function[])(char **) = {
	&shell_cd,
	&shell_exit};

/**
 * number_of_builtin - to fined the number of commands
 *
 * Return: int
 */
int number_of_builtin(void)
{
	return (sizeof(built_in_str) / sizeof(char *));
}

/* bellow are the required command */
/**
 * shell_cd - the cd command
 *
 * @args: the argument passed
 * Return: int
 */
int shell_cd(char **args)
{
	char *home_dir;
	if (args[1] == NULL || strcmp(args[1], "-") == 0)
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
 * return: int
 */
int shell_exit(char **args)
{
	int i;
	int len;
	if (args[1] != NULL)
	{
		len = strlen(args[1]);
		for (i = 0; i < len; i++)
		{
			if (!isdigit(args[1][i]))
			{
				dprintf(2, "./hsh: 1: exit: Illegal number: %s\n", args[1]);
				exit(EXIT_SUCCESS);
			}
		}
	}
	exit(EXIT_SUCCESS);
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
	for (i = 0; i < number_of_builtin(); i++)
	{
		if (strcmp(args[0], built_in_str[i]) == 0)
		{
			return (builtin_function[i](args));
		}
	}
	/* if no argument is found */
	return (shell_execute(args));
}
