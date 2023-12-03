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

char *array[] = {"cd", "exit"};

int (*get_array[])(char **) = {&cd, &Exit};

int cd(char **args)
{

}
int Exit(char **args)
{
	return (1);
	
}

int eacute(char **args)
{
	int i = 0;
	for (i = 0; i < strlen(array); i++)
	{
		if (strcmp(args[0], array[i]) == 0)
		{
			return (get_array[i](args));
		}
	}
	return ()
}


























char *built_in_str[] =
	{
		"cd",
		"exit"};

int shell_cd(char **args)
{
	chdir(args[1]);
	return (1);
}

int shell_exit(char **args)
{
	return (1);
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
