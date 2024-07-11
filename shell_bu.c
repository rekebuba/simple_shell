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
    char *old_pwd = getenv("OLDPWD");
    char cwd[1024];

    // Handle "cd" or "cd -"
    if (args[1] == NULL || strcmp(args[1], "-") == 0)
    {
        if (args[1] == NULL)
        {
            home_dir = getenv("HOME");
            if (home_dir == NULL)
            {
                dprintf(2, "./hsh: 1: cd: HOME not set\n");
                return 1;
            }
            if (chdir(home_dir) != 0)
            {
                dprintf(2, "./hsh: 1: cd: can't cd to %s\n", home_dir);
                return 1;
            }
        }
        else if (strcmp(args[1], "-") == 0)
        {
            if (old_pwd == NULL)
            {
                dprintf(2, "./hsh: 1: cd: OLDPWD not set\n");
                return 1;
            }
            if (chdir(old_pwd) != 0)
            {
                dprintf(2, "./hsh: 1: cd: can't cd to %s\n", old_pwd);
                return 1;
            }
            printf("%s\n", old_pwd);  // Print the old directory
        }
    }
    else
    {
        if (chdir(args[1]) != 0)
        {
            dprintf(2, "./hsh: 1: cd: can't cd to %s\n", args[1]);
            return 1;
        }
    }

    // Update OLDPWD and PWD environment variables
    setenv("OLDPWD", getenv("PWD"), 1);
    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        setenv("PWD", cwd, 1);
    }
    else
    {
        perror("getcwd() error");
        return 1;
    }

    return 0;
}

/**
 * shell_exit - the exit command
 *
 * @line: the string passed
 * Return: void
 */
void shell_exit(char *line)
{
	int i = 0, l;
	char *result = NULL;

	if (strstr(line, "exit") == NULL)
	{
		return;
	}

	result = _strtok(line, " ");
	result = _strtok(NULL, " ");
	if (result != NULL)
	{
		for (i = 0; result[i]; i++)
		{
			if (!isdigit(result[i]))
			{
				dprintf(2, "./hsh: 1: exit: Illegal number: %s\n", result);
				if (!isatty(STDIN_FILENO))
				{
					free(line);
					exit(2);
				}
				return;
			}
		}
		l = _atoi(result);
		free(line);
		exit(l);
	}
	free(line);
	exit(EXIT_SUCCESS);
}

/**
 * shell_launch - all the builtin are executed inside this func
 * @user_input: users input
 * @args: the argument passed
 * Return: int
 */
int shell_launch(char *user_input, char **args)
{
	int i;
	char *built_in_str[] = {"cd"};

	int (*builtin_function[])(char **) = {&shell_cd};
	int number_of_builtin = sizeof(built_in_str) / sizeof(char *);

	if (args[0] == NULL)
	{
		return (0);
	}

	for (i = 0; i < number_of_builtin; i++)
	{
		if (_strcmp(args[0], built_in_str[i]) == 0)
		{
			return (builtin_function[i](args));
		}
	}
	/* if no argument is found */
	return (shell_execute(user_input, args));
}
