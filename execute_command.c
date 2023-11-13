#include "shell.h"

/**
 * execute_command - executes the provided commands using `execve
 * @command: pointer to a character
 *
 * Return: SHELL_EXIT if command is exit otherwise SHELL_SUCCESS
 */

int execute_command(char *command)
{
	pid_t pid_child;
	int status;

	if (strcmp(command, "exit") == 0)
		return (SHELL_EXIT);

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
		if (execve(command, (char *const []){command, NULL}, (char *const[]){ NULL }) == -1)
		{
			_error("No such file or directory");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		/* parent process*/
		waitpid(pid_child, &status, 0);
	}

	return (SHELL_SUCCESS);
}
