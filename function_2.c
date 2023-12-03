#include "main.h"

/**
 * shell_read_line - it reads a line imputed bu the user
 *
 * Return: char*
 */
char *shell_read_line(void)
{
    char *buffer = malloc(BUFFER * sizeof(char));
    int index = 0;
    int buffer_size = BUFFER;
    int c;
    int i;
    int len;

    if (!buffer)
    {
        perror("ERROR: failed to allocate memory\n");
        exit(EXIT_FAILURE);
    }
    while (true)
    {
        /*read character by character*/
        c = getchar();
        if (c == EOF || c == '\n')
        {
            buffer[index] = '\0';
            removeWhiteSpace(buffer);
            len = strlen(buffer);
            for (i = 0; i < len; i++)
            {
                if (buffer[i] == '#')
                {
                    buffer[i] = '\0';
                    return (buffer);
                }
            }
            return (buffer);
        }
        else
        {
            buffer[index] = c;
        }
        index++;
        /* if we have exceeded the buffer, reallocate*/
        if (index >= buffer_size)
        {
            buffer_size += BUFFER;
            buffer = realloc(buffer, buffer_size);
            if (!buffer)
            {
                perror("ERROR: failed to allocate memory\n");
                exit(EXIT_FAILURE);
            }
        }
    }
}

/**
 * removeWhiteSpace - it removes unnecessary whitespace
 * @str: the string that needs to be modified
 * Return: void
 */
void removeWhiteSpace(char *str)
{
    char *p1 = str; /* pointer to iterate through the input string */
    char *p2 = str; /* pointer to write the non-space characters to */

    while (*p1 != '\0')
    {
        if (!isspace(*p1))
        {
            *p2 = *p1;
            p2++;
        }
        p1++;
    }

    *p2 = '\0';
}

/**
 * _strtok - used to tokenize a string besed on specified delimeter
 *
 * @str: the string that needs to be tokenize
 * @delimiter: delimiters
 * Return: char*
 */
char *_strtok(char *str, const char *delimiter)
{
    static char *buffer = NULL;
    char *token;
    if (str != NULL)
    {
        buffer = str;
    }
    if (buffer == NULL)
    {
        return (NULL);
    }
    token = buffer;
    buffer += strcspn(buffer, delimiter);
    if (*buffer != '\0')
    {
        *buffer = '\0';
        buffer++;
    }
    else
    {
        buffer = NULL;
    }
    return (token);
}

/**
 * shell_execute - it executes the command entered
 *
 * @args: the argument passed
 * Return: int
 */
int shell_execute(char **args)
{
    pid_t pid;
    int status;

    pid = fork();

    if (pid == 0)
    {
        /* were in the chilled processor */
        if (execvp(args[0], args) == -1)
        {
            exit(EXIT_FAILURE);
        }
    }
    else if (pid < 0)
    {
        /* failed to fork */
        perror("failed to fork\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        /* were in the parent processor */
        do
        {
            waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    return (1);
}
