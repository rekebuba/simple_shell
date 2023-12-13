#include "main.h"

/**
 * get_home_directory - Get the home directory object
 * 
 * Return: char*
 */
char *get_home_directory()
{
	char *home_dir = getenv("HOME");
	return home_dir != NULL ? home_dir : "";
}

/**
 * update_pwd_env_variable - update_pwd_env_variable
 */
void update_pwd_env_variable()
{
	char cwd[1024];
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		setenv("PWD", cwd, 1);
	}
	else
	{
		perror("getcwd");
	}
}

/**
 * shell_cd - the cd command
 *
 * @args: the argument passed
 * Return: int
 */
int shell_cd(char **args)
{
	if (args[1] == NULL || strcmp(args[1], "~") == 0)
	{
		char *home_dir = get_home_directory();
		if (chdir(home_dir) != 0)
		{
			perror("cd");
		}
	}
	else if (strcmp(args[1], "-") == 0)
	{
		char *previous_dir = getenv("OLDPWD");
		if (previous_dir != NULL)
		{
			if (chdir(previous_dir) != 0)
			{
				perror("cd");
			}
			else
			{
				printf("%s\n", previous_dir);
				setenv("OLDPWD", get_home_directory(), 1);
				update_pwd_env_variable();
			}
		}
		else
		{
			printf("cd: OLDPWD not set\n");
		}
	}
	else
	{
		if (chdir(args[1]) != 0)
		{
			perror("cd");
		}
		else
		{
			setenv("OLDPWD", get_home_directory(), 1);
			update_pwd_env_variable();
		}
	}

	return 0;
}

/*int shell_cd(char **args)
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
}*/

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
 * shell_launch - all the builtin are executed inside this func
 *
 * @args: the argument passed
 * Return: int
 */
int shell_launch(char **args)
{
	int i;
	char *built_in_str[] = {"cd", "exit"};

	int (*builtin_function[])(char **) = {&shell_cd, &shell_exit};
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
