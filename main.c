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

int exit_command(char **args)
{
	return (0);
}