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

void _loop(void);
void display_prompt(void);
int execute_command(char *command);
void _error(const char *message);
char *readline(void);

#endif
