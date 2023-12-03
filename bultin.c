#include "main.h"

char *built_in_str[] =
	{
		"cd",
		"exit"};

int (*builtin_function[])(char **) =
	{
		&shell_cd,
		&shell_exit};

int number_of_builtin(void)
{
	return (sizeof(built_in_str) / sizeof(char *));
}


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
				dprintf(2, "cd: can't cd to %s\n", args[1]);
			}
		}
	}
	else
	{
		if (chdir(args[1]) != 0)
		{
			dprintf(2, "cd: can't cd to %s\n", args[1]);
		}
	}

	return (1);
}

int shell_exit(char **args)
{
	int i;
	if (args[1] != NULL)
	{
		for (i = 0; i < strlen(args[1]); i++)
		{
			if (!isdigit(args[1][i]))
			{
				dprintf(2, "exit: Illegal number: %s\n", args[1]);
				exit(1);
			}
		}
	}
	exit(0);
}

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

	return (shell_execute(args));
}
