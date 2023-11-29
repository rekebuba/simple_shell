#include <stdio.h>

/**
 * _pow - function to raise a number by exponent
 * @base: int
 * @exponent: int
 * Return: unsigned int
 */
unsigned int _pow(int base, int exponent)
{
	unsigned int result = 1;
	int i;

	for (i = 0; i < exponent; i++)
	{
		result *= base;
	}

	return (result);
}

/**
 * binary_to_uint - converts a binary number to an unsigned int.
 * @b: is pointing to a string of 0 and 1 chars
 * Return: unsigned int
 */
unsigned int binary_to_uint(const char *b)
{
	int len = strlen(b), index = 0, j;
	unsigned int result = 0;

	if (b == NULL)
	{
		return (0);
	}

	for (j = len - 1; j >= 0; j--)
	{
		if (b[j] == '0')
		{
			index++;
		}
		else if (b[j] == '1')
		{
			result += _pow(2, index);
			index++;
		}
		else
			return (0);
	}

	return (result);
}
