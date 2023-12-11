#include "main.h"

/**
 * _strlen - checks the length of a string
 * 
 * @str: the string passed
 * Return: size_t
 */
size_t _strlen(const char *str)
{
    const char *s = str;
    while (*s)
    {
        s++;
    }
    return (s - str);
}
