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
	if (strcmp(argv[0], "exit") == 1)
	{
		return 0;
	}
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
	chdir(args[1]);
	return (1);
}

int shell_exit(char **args)
{
	return (1);
}

int (*built_in_function[])(char **) =
	{
		&shell_cd,
		&shell_exit};

