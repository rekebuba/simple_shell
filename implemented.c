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

    return status;
}

int _strcmp(const char *str1, const char *str2)
{
    while (*str1 && (*str1 == *str2))
    {
        str1++;
        str2++;
    }

    return *(unsigned char *)str1 - *(unsigned char *)str2;
}
