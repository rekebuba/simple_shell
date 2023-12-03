#include "main.h"

/*
 * shell_loop -
 *
 */
void shell_loop(void)
{
    char *line;
    char **args;
    int status;

    do
    {
        dprintf(1, "$ ");
        line = shell_read_line();
        args = shell_split_line(line);
        status = shell_launch(args);

        free(line);
        free(args);
    } while (status);

    exit(EXIT_FAILURE);
}
/**
 * shell_split_line -
 *
 * @line:
 * Return: char**
 */
char **shell_split_line(char *line)
{
    int buffer_size = BUFFER;
    int index = 0;
    char **tokens = malloc(buffer_size * sizeof(char *));
    char *token;

    if (!tokens)
    {
        fprintf(stderr, "ERROR: failed to allocate memory\n");
        exit(EXIT_FAILURE);
    }

    token = _strtok(line, TOK_DELIM);
    while (token != NULL)
    {
        tokens[index] = token;
        index++;

        if (index >= BUFFER)
        {
            buffer_size += BUFFER;
            tokens = realloc(tokens, buffer_size * sizeof(char *));
            if (!tokens)
            {

                fprintf(stderr, "ERROR: failed to allocate memory\n");
                exit(EXIT_FAILURE);
            }
        }
        token = _strtok(NULL, TOK_DELIM);
    }
    tokens[index] = NULL;
    return (tokens);
}
