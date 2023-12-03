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
