#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define END_OF_FILE -2
#define EXIT -3
#define SHELL_SUCCESS 0
#define SHELL_EXIT 1
#define MAX_ARGS 128

void _loop(void);
void display_prompt(void);
int execute_command(char *command);
void _error(const char *message);
char *readline(void);
void tokenize_command(char *command, char *args[], size_t *arg_count);
void execute_child(char *args[]);
void execute_parent(pid_t child_pid, int *status);
int execute_command(char *command);

/* Global environemnt */
extern char **environ;
char *name;
int hist;

/* Builtins environment*/
int (*get_builtin(char *command))(char **args, char **front);
int shellby_exit(char **args, char **front);
int shellby_env(char **args, char __attribute__((__unused__)) **front);
int shellby_setenv(char **args, char __attribute__((__unused__)) **front);
int shellby_unsetenv(char **args, char __attribute__((__unused__)) **front);
int shellby_cd(char **args, char __attribute__((__unused__)) **front);
int shellby_alias(char **args, char __attribute__((__unused__)) **front);
int shellby_help(char **args, char __attribute__((__unused__)) **front);

/* Error Handling shell*/
int create_error(char **args, int err);
char *error_env(char **args);
char *error_1(char **args);
char *error_2_exit(char **args);
char *error_2_cd(char **args);
char *error_2_syntax(char **args);
char *error_126(char **args);
char *error_127(char **args);

#endif
