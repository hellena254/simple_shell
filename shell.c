#include "shell.h"

/**
 * _loop - main loop of the shell, prompts the user for input,
 *	reading the command, executing it and error handling
 */

void _loop(void)
{
	char *line;
	int status;

	while (1)
	{
		display_prompt();
		line = readline();

		/* handle end-of-file*/
		if (line == NULL)
			break;

		status = execute_command(line);

		free(line);

		if (status == SHELL_EXIT)
			break;
	}
}

/**
 * display_prompt - prints the shell prompt (`#cisfun$`)
 */

void display_prompt(void)
{
	printf("#cisfun$ ");
}

/**
 * _error - prints error message with shell name prefix
 * @message: the error message to print
 */

void _error(const char *message)
{
	fprintf(stderr, "./shell: %s\n", message);
}
