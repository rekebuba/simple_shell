#include "main.h"

/**
 * main -
 *
 * @argc
 * @argv
 * Return: int
 */
int main(int argc, char **argv)
{

	shell_loop();

	exit(EXIT_FAILURE);
}

/**
 * Error -
 *
 * @param args
 */
void Error(char **args)
{
	dprintf(2, "%s: not found\n", args[0]);
}

char *built_in_str[] =
	{
		"cd",
		"exit"};

int shell_cd(char **args)
{
	if (args[1] == NULL)
	{
		chdir("~");
		dprintf(2, "sus\n");
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
	return (0);
}

int (*builtin_function[])(char **) =
	{
		&shell_cd,
		&shell_exit};

int number_of_builtin()
{
	return (sizeof(built_in_str) / sizeof(char *));
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
