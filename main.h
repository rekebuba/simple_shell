#ifndef SIMPLE_SHELL
#define SIMPLE_SHELL

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <sys/wait.h>
#include <unistd.h>
#include <ctype.h>
#include <signal.h>
#include <errno.h>



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

char **command(char *arg);

int _space(int c);
size_t _strlen(const char *str);

char *char_in_str(char *s, char c);
int _system(const char *command);
int _strcmp(const char *str1, const char *str2);
size_t _strcspn(const char *str1, const char *str2);

#endif
