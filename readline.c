#include "shell.h"

/**
 * readline - reads a line of input from the user
 * Return: a dynamically allocated string
 */

char *readline(void)
{
	char *line = NULL;
	size_t length = 0;
	ssize_t read_line = getline(&line, &length, stdin);

	if (read_line == -1)
	{
		/* encountered an error or end-of-file*/
		free(line);
		return (NULL);
	}

	/* handle newline characters*/
	if (line[read_line - 1] == '\n')
		line[read_line - 1] = '\0';

	return (line);
}
