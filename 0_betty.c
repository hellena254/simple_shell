#include <stdio.h>

/**
 * main - entry point
 * @ac: argument count
 * @av: array of strings representing the command line arguments
 *
 * Return: Always (0) success
 */

int main(int __attribute__((unused)) ac, char *av[])
{
	int i;

	/*iterate through each cl argument*/
	for (i = 0; av[i] != NULL; i++)
	{
		printf("Argument %d: %s\n", i, av[i]);
	}

	return (0);
}
