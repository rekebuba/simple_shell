#include "main.h"

/**
 * main - the main program
 *
 * @argc: number of argument count
 * @argv: the argument passed
 * Return: int
 */
int main(int argc, char **argv)
{
	(void) argc;
	(void) argv;
	shell_loop();

	exit(EXIT_FAILURE);
}
