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

/**
 * struct Node - a single linked list
 * @key: key
 * @value: value
 * @next: points to the next node
 * Description: singly linked list node structure
 */
struct Node
{
	char *key;
	char *value;
	struct Node *next;
};

/**********************shell.c***********************************/
int shell(struct Node **head, char *user_input, int prev_status);
int file_as_input(struct Node *head, char **args);
void free_mem(char *user_input, char **args);
void _signal(int signal);

/**********************handleString.c***********************************/
int array_len(char **args);
char *_strtok(char *str, const char *delimiter);
int _strcmp(const char *str1, const char *str2);
size_t _strcspn(const char *str1, const char *str2);
char **tokenize(char *arg, char *delimeter);

/**********************node_alias1.c***********************************/
int shell_alias(struct Node **head, char **args);
struct Node *createNode(char *key, char *value);
void check_existing_node(struct Node **head, char *alias);
void appendNode(struct Node **head, char *key, char *value);
void removeNode(struct Node **head, struct Node *nodeToRemove);

/**********************node_alias2.c***********************************/
void printList(struct Node *head, char *alias);
void freeList(struct Node *head);

/**********************shell_commands1.c***********************************/
int shell_cd(struct Node **head, char **args);
void shell_exit(struct Node **head, char *line, int prev_status);
void is_comment(char *);

/**********************shell_commands2.c***********************************/
int logical_ope(struct Node **head, char *line);
int is_colon(struct Node **head, char *line);
void set_unset_env(char **args);

/**********************shell_execute.c***********************************/
int shell_launch(struct Node **head, char *user_input, char **args, int);
int shell_execute(char *user_input, char **args, int prev_status);

/**********************valid_command.c***********************************/
char *read_line(char *line);
ssize_t get_line(char **line_ptr, size_t *n, FILE *stream);
char **shell_split_line(struct Node **head, char *line);
void valid_input(struct Node **head, char **args);
char *assign_value(struct Node **head, char *key);

#endif
