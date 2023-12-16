#include "shell.h"

/**
 * built_in_cmd - Checks if a command is a built-in command and executes
 * @args: param to be checked
 * Return: 1 or 0
 */

int built_in_cmd(char **args)
{
	if (args[0] == NULL)
		return (1);
	if (strcmp(args[0], "exit") == 0)
		return (exit_shell(args));
	if (strcmp(args[0], "env") == 0)
		return (show_env());
	if (strcmp(args[0], "cd") == 0)
		return (change_dir(args));
	if (strcmp(args[0], "setenv") == 0)
		return (set_env(args));
	if (strcmp(args[0], "unsetenv") == 0)
		return (unset_env(args));

	return (0);
}

/**
 * set_env - Sets or updates the value
 * @args: The array of command and arguments
 * Return: 0 on success, 1 on failure
 */
int set_env(char **args)
{
	if (args[1] == NULL || args[2] == NULL || args[3] != NULL)
	{
		fprintf(stderr, "Usage: setenv VARIABLEVALUE\n");
		return (1);
	}
	if (setenv(args[1], args[2], 1) == -1)
	{
		perror("setenv error");

		return (1);
	}

	return (0);
}

/**
 * unset_env - Unsets an environmental variable
 * @args: The array of command and arguments
 * Return: 0 on success, 1 on failure
 */

int unset_env(char **args)
{
	if (args[1] == NULL || args[2] != NULL)
	{
		fprintf(stderr, "Usage: unsetenv VARIABLE\n");

		return (1);
	}

	if (unsetenv(args[1]) == -1)
	{
		perror("unsetenv error");

		return (1);
	}

	return (0);
}

/**
 * exit_shell - Exits the shell program
 * @args: The array of command and arguments
 * Return: suceess on exit
 */

int exit_shell(char **args)
{
	if (args[1] != NULL)
	{
		int status = atoi(args[1]);

		exit(status);

	}
	else
	{
		exit(EXIT_SUCCESS);
	}
}

/**
 * show_env - Displays the environment
 * Return: 1
 */

int show_env(void)
{
	char **env = environ;

	while (*env)
	{
		printf("%s\n", *env);
		env++;
	}

	return (1);
}

/**
 * change_dir - Changes the current working dir
 * @args: The array of command and arguments
 * Return: 1 on success, 0 on failure
 */
int change_dir(char **args)
{
	char *dir;

	if (args[1] == NULL)
		dir = get_env("HOME");
	else if (strcmp(args[1], "-") == 0)
		dir = get_env("OLDPWD");
	else
		dir = args[1];

	if (chdir(dir) != 0)
	{
		perror("cd error");
		return (1);
	}
	else
	{
		char cwd[BUFSIZE];

		if (getcwd(cwd, sizeof(cwd)) != NULL)
		{
			setenv("PWD", cwd, 1);
			setenv("OLDPWD", dir, 1);
		}
		else
		{
			perror("getcwd error");
		}
	}

	return (1);
}

/**
 * get_env - Gets the value of an environmental var
 * @name: The name of the environmental var
 * Return: The value of the environmental var
 */

char *get_env(const char *name)
{
	char *env_var = getenv(name);

	if (env_var == NULL)
	{
		fprintf(stderr, "%s: Environmental variable not found.\n", name);
		return (NULL);
	}
	return (env_var);
}





