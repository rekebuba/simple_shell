#ifndef SIMPLE_SHELL
#define SIMPLE_SHELL

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <ctype.h>
#include <signal.h>



#define BUFFER 1024
#define TOK_DELIM " \t\r\n\a\"" /* the delimeter used to tokenize*/

void shell_loop(void);
char **shell_split_line(char *line);
char *shell_read_line(void);
char *_strtok(char *str, const char *delimiter);
int shell_execute(char **args);

int shell_launch(char **args);
int shell_cd(char **args);
int shell_exit(char **args);

void _signal(int signal);

void removeWhiteSpace(char *str);


#endif
