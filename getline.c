#include "shell.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * get_line - Reads a line from standard input
 * Return: The line read from standard input
 */
char *get_line(void)
{
	size_t bufsize = 0;
	char *line = NULL;

	if (getline(&line, &bufsize, stdin) == -1)
	{
		free(line);
		return (NULL);
	}

	return (line);
}
