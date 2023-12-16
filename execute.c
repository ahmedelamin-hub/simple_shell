#include "shell.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

/**
 * is_dir - Checks if a given path is a directory.
 * @path: path to check
 * Return: 1 if path is dir or 0
 */

int is_dir(const char *path)
{
	struct stat path_stat;

	if (stat(path, &path_stat) != 0)
	{
		return (0);
	}
	return (S_ISDIR(path_stat.st_mode));
}

/**
 * find_cmd - finds function
 * @cmd: command
 * Return: full path
 */

char *find_cmd(const char *cmd)
{
	char *path = getenv("PATH");
	char *path_copy = strdup(path);
	char *token = strtok(path_copy, ":");

	while (token != NULL)
	{
		char *full_path = malloc(strlen(token) + strlen(cmd) + 2);

		sprintf(full_path, "%s/%s", token, cmd);

		if (access(full_path, F_OK) == 0 && !is_dir(full_path))
		{
			free(path_copy);
			return (full_path);
		}

		free(full_path);
		token = strtok(NULL, ":");
	}

	free(path_copy);
	return (NULL);
}
/**
 * execute_cmd - Executes a command with the given
 * @arguments: An array of arguments, with the command first elem
 * Return: exit status
 */

int execute_cmd(char **arguments)
{
	pid_t pid;
	int status;
	char *full_path;

	if ((arguments[0][0] == '/' || strstr(arguments[0], "..") != NULL))
	{
		full_path = strdup(arguments[0]);
	}
	else
	{
		full_path = find_cmd(arguments[0]);
	}

	if (full_path == NULL || access(full_path, F_OK) != 0 || is_dir(full_path))
	{
		fprintf(stderr, "(shellelmo) $ checking directory: %s\n", arguments[0]);
		fprintf(stderr, "(stderr)[Shell: Command not found:%s\n](Length: %lu)\n",
				arguments[0], strlen(arguments[0]) + 45);
		free(full_path);
		return (1);
	}

	pid = fork();

	if (pid == 0)
	{
		if (execve(full_path, arguments, environ) == -1)
		{
			perror("execve failed");
			exit(EXIT_FAILURE);
		}
		exit(EXIT_SUCCESS);
	}
	else if (pid < 0)
	{
		perror("fork failed");
	}
	else
	{
		waitpid(pid, &status, 0);
	}

	free(full_path);
	return (status);
}

