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
	int status;
	(void) argc;
	(void) argv;
	
	signal(SIGINT, _signal);
	

	status = shell_loop();

	return(status);
}

/**
 * _signal - handle Ctr+C
 * @signal: when the Ctrl+c is received
 * Return: Void
 */
void _signal(int signal)
{
	(void)signal;
	printf("\n$ ");
	fflush(stdout);
}
