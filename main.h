#ifndef SIMPLE_SHELL
#define SIMPLE_SHELL

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define BUFFER 1024
#define TOK_DELIM " \t\r\n\a" /* the delimeter used to tokenize*/

void shell_loop(void);
char **shell_split_line(char *line);
char *shell_read_line(void);
char *_strtok(char *str, const char *delimiter);

#endif