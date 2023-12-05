#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 100
#define MAX_ARGUMENTS 10

void executeCommand(char* command) {
    char* arguments[MAX_ARGUMENTS];
    int argCount = 0;

    // Tokenize the command into arguments
    char* token = strtok(command, " \t\n");
    while (token != NULL && argCount < MAX_ARGUMENTS - 1) {
        arguments[argCount++] = token;
        token = strtok(NULL, " \t\n");
    }
    arguments[argCount] = NULL;

    // Fork a new process to execute the command
    pid_t pid = fork();

    if (pid < 0) {
        // Error forking
        perror("fork");
    } else if (pid == 0) {
        // Child process
        execvp(arguments[0], arguments);
        perror("execvp");
        exit(EXIT_FAILURE);
    } else {
        // Parent process
        int status;
        waitpid(pid, &status, 0);
    }
}

int main() {
    char command[MAX_COMMAND_LENGTH];

    while (1) {
        printf("$ ");
        fflush(stdout);

        // Read the command from the user
        if (fgets(command, sizeof(command), stdin) == NULL) {
            break;
        }

        // Check for a piped command
        char* pipeToken = strchr(command, '|');
        if (pipeToken != NULL) {
            // Split the command into two parts
            *pipeToken = '\0';
            char* firstCommand = command;
            char* secondCommand = pipeToken + 1;

            // Create a pipe
            FILE* pipeFile = popen(firstCommand, "r");
            if (pipeFile == NULL) {
                perror("popen");
                continue;
            }

            // Execute the second command with the pipe as input
            char line[MAX_COMMAND_LENGTH];
            while (fgets(line, sizeof(line), pipeFile) != NULL) {
                printf("$ %s", line);
                fflush(stdout);
                executeCommand(secondCommand);
            }

            pclose(pipeFile);
        } else {
            // No pipe, execute the command directly
            executeCommand(command);
        }
    }

    return 0;
}
