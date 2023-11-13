#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

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

#endif
