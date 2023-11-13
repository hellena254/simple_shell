#include "shell.h"

/**
 * tokenize_command - tokenizes a command line into an array oof strings
 * @command: the command line to tokenize
 * @args: An array to store the command and its arguments
 * @arg_count: pointer to the count of arguments in the array
 */
void tokenize_command(char *command, char *args[], size_t *arg_count)
{
	char *token = strtok(command, " ");

	while (token != NULL && *arg_count < MAX_ARGS - 1)
	{
		args[(*arg_count)++] = token;
		token = strtok(NULL, " ");
	}
	/* null-terminate the array*/
	args[*arg_count] = NULL;
}

/**
 * execute_child - execute the command in the child process
 * @args: An array containing the command and its arguments
 */
void execute_child(char *args[])
{
	execve(args[0], args, NULL);
	_error("No such file or directory");
	exit(EXIT_FAILURE);
}

/**
 * execute_parent- waits for the child process to finish in the parent process
 * @pid_child: The pid of the child process
 * @status: Pointer to store the exit status of the child process
 */
void execute_parent(pid_t pid_child, int *status)
{
	waitpid(pid_child, status, 0);
}

/**
 * execute_command - executes command entered by the user
 * @command: command entered by the user
 *
 * Return: SHELL_EXIT if command is exit otherwise SHELL_SUCCESS
 */
int execute_command(char *command)
{
	pid_t pid_child;
	int status;
	size_t arg_count = 0;
	char *args[MAX_ARGS];

	if (strcmp(command, "exit") == 0)
		return (SHELL_EXIT);

	tokenize_command(command, args, &arg_count);

	pid_child = fork();
	if (pid_child == -1)
	{
		/* fork failed*/
		_error("failed to create child process");
		return (SHELL_SUCCESS);
	}

	if (pid_child == 0)
	{
		/* child process*/
		execute_child(args);
	}
	else
	{
		/* parent process*/
		execute_parent(pid_child, &status);
	}

	return (SHELL_SUCCESS);
}
