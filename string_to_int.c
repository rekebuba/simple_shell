#include "main.h"

/**
 * _atoi - convert string to integer
 * @str: the string to be converted
 * Return: int 
 */
int _atoi(const char *str)
{
	int result = 0;
	int sign = 1;

	while (isspace(*str))
	{
		str++;
	}

	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
		{
			sign = -1;
		}
		str++;
	}

	while (isdigit(*str))
	{
		result = result * 10 + (*str - '0');
		str++;
	}

	return result * sign;
}
