#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <ctype.h>
#include <signal.h>
#include <errno.h>

#define MAX_COMMAND_LENGTH 100

void handle_signal(int signal)
{
    // Handle the signal, if needed
    exit(0);
}

char *get_line()
{
    char *line = NULL;
    ssize_t read;
    size_t len = 0;

    printf("$ ");
    fflush(stdout);

    read = getline(&line, &len, stdin);

    if (read == -1)
    {
        if (isatty(STDIN_FILENO))
            printf("\n");
        free(line);
        line = NULL;
    }
    else
    {
        line[_strcspn(line, "\n")] = '\0'; // Remove trailing newline character
    }

    return line;
}

char **split_line(char *line)
{
    char **args = malloc(MAX_COMMAND_LENGTH * sizeof(char *));
    char *token;
    int argCount = 0;

    if (!args)
    {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, " ");
    while (token != NULL)
    {
        args[argCount] = token;
        argCount++;
        token = strtok(NULL, " ");
    }
    args[argCount] = NULL;

    return args;
}

int launch_command(char **args)
{
    pid_t pid;
    int status;

    pid = fork();

    if (pid == 0)
    {
        // Child process
        if (execvp(args[0], args) == -1)
        {
            perror("Error executing command");
            exit(EXIT_FAILURE);
        }
    }
    else if (pid < 0)
    {
        // Forking failed
        perror("Error forking child process");
        exit(EXIT_FAILURE);
    }
    else
    {
        // Parent process
        do
        {
            waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    return WEXITSTATUS(status);
}

int main(int argc, char **argv)
{
    char *line;
    char **args;
    int status = 0;

    (void)argc;
    (void)argv;

    signal(SIGINT, handle_signal);

    do
    {
        line = get_line();

        if (line != NULL)
        {
            args = split_line(line);

            if (args[0] != NULL)
            {
                status = launch_command(args);
            }

            free(args);
            free(line);
        }
    } while (status == 0);

    if (status == 1)
    {
        return 127;
    }

    return status;
}
