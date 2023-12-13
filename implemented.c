#include "main.h"

/**
 *_strchr - locates a character in a string like strchr()
 *@s: the string to be parsed
 *@c: the character to look for
 *Return: (s) a pointer to the memory area
 */
char *char_in_str(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}

/**
 * _system - execute a command
 * 
 * @command: string passed 
 * Return: int 
 */
int _system(const char *command)
{
	pid_t pid;
	int status;

	if (command == NULL)
		return -1;

	pid = fork();
	if (pid < 0)
	{
		return -1;
	}
	else if (pid == 0)
	{
		execl("/bin/sh", "sh", "-c", command, (char *)NULL);
		_exit(127); 
	}
	else
	{
		while (waitpid(pid, &status, 0) == -1)
		{
			if (errno != EINTR)
			{
				status = -1;
				break;
			}
		}
	}

	return (status);
}

/**
 * _strcmp - compare two strings 
 * 
 * @str1: string 1
 * @str2: string 2
 * Return: int 
 */
int _strcmp(const char *str1, const char *str2)
{
	while (*str1 && (*str1 == *str2))
	{
		str1++;
		str2++;
	}

	return (*(unsigned char *)str1 - *(unsigned char *)str2);
}

/**
 * _strcspn - _strcspn
 * 
 * @str1: string 1
 * @str2: string 2
 * Return: size_t 
 */
size_t _strcspn(const char *str1, const char *str2)
{
	const char *p1, *p2;
	size_t count = 0;
	
	for (p1 = str1; *p1 != '\0'; p1++)
	{
		for (p2 = str2; *p2 != '\0'; p2++)
		{
			if (*p1 == *p2)
				return count;
		}
		
		count++;
	}
	
	return (count);
}
