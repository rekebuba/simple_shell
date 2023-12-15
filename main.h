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
#include <errno.h>



#define BUFFER 1024
#define TOK_DELIM " \t\r\n\a\"" /* the delimeter used to tokenize*/

int shell_loop(void);
char *read_line();
char **shell_split_line(char *line);
void is_comment(char *);
char *_strtok(char *str, const char *delimiter);
int shell_execute(char **args);

int shell_launch(char **args);
int shell_cd(char **args);
int shell_exit(char **args);
int _setenv(char **args);
int _unsetenv(char **args);
void _signal(int signal);


char **command(char *arg);

int _space(int c);
size_t _strlen(const char *str);

char *char_in_str(char *s, char c);
int _system(const char *command);
int _strcmp(const char *str1, const char *str2);
size_t _strcspn(const char *str1, const char *str2);

ssize_t get_line(char **line_ptr, size_t *n, FILE *stream);
int _atoi(const char *str);


#endif
