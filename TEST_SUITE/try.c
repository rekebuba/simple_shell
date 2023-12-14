#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[])
{
    int interactive = isatty(STDIN_FILENO);
    char *buffer = malloc(BUFFER_SIZE * sizeof(char));

    while (1)
    {
        if (interactive)
        {
            printf("$ "); // Display prompt
        }

        if (fgets(buffer, BUFFER_SIZE, stdin) == NULL)
        {
            printf("\n");
            break; // End of file condition (Ctrl+D)
        }

        // Remove trailing newline character
        buffer[_strcspn(buffer, "\n")] = '\0';

        // Fork a child process
        pid_t pid = fork();

        if (pid < 0)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        else if (pid == 0)
        {
            // Child process

            // Redirect standard input if running in non-interactive mode
            if (!interactive)
            {
                int fd = open("/dev/null", O_RDONLY);
                if (fd == -1)
                {
                    perror("open");
                    exit(EXIT_FAILURE);
                }
                if (dup2(fd, STDIN_FILENO) == -1)
                {
                    perror("dup2");
                    exit(EXIT_FAILURE);
                }
                close(fd);
            }

            if (execlp(buffer, buffer, NULL) == -1)
            {
                perror("execlp");
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            // Parent process
            int status;
            waitpid(pid, &status, 0);

            int exit_status = WEXITSTATUS(status);

            if (interactive)
            {
                if (WIFEXITED(status))
                {
                    printf("Child process exited with status %d\n", exit_status);
                }
                else if (WIFSIGNALED(status))
                {
                    int signal_number = WTERMSIG(status);
                    printf("Child process terminated by signal %d\n", signal_number);
                }
            }
            else
            {
                if (exit_status == 0)
                {
                    printf("Command executed successfully\n");
                }
                else
                {
                    printf("Command execution failed\n");
                }
            }
        }
    }

    free(buffer);
    return 0;
}
