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

char *read_line();
char **shell_split_line(char *line);
void is_comment(char *);
char *_strtok(char *str, const char *delimiter);
int shell_execute(char *user_input, char **args, int prev_status);
int shell_launch(char *user_input, char **args,  int prev_status);
int shell_cd(char **args);
void shell_exit(char *line);
void _signal(int signal);
char **tok_colon(char *arg);
size_t _strlen(const char *str);
int _system(const char *command);
int _strcmp(const char *str1, const char *str2);
size_t _strcspn(const char *str1, const char *str2);
ssize_t get_line(char **line_ptr, size_t *n, FILE *stream);
int _atoi(const char *str);
int is_colon(char *line);
int logical_ope(char *line);
void set_unset(char **args);
void free_mem(char *user_input, char **args);
int array_len(char **args);
void valid_input(char **args);
int file_as_input(char **args);
int shell(char *user_input, int prev_status);

#endif
