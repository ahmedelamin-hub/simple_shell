#include "shell.h"
#include <pwd.h>
#include <unistd.h>

/**
 * main - Entry point for the shell program.
 * Return: Always 0
 */

int main(void)
{
	char *line;
	char **args;
	int status;

	char *username = NULL;

	if (isatty(STDIN_FILENO))
	{

		struct passwd *pw = getpwuid(getuid());

		username = pw->pw_name;

		printf("(%s)$ elmo ", username);
	}

	while ((line = get_line()) != NULL)
	{
		args = split_line(line);
		status = built_in_cmd(args);

		if (!status)
			status = execute_cmd(args);
		if (isatty(STDIN_FILENO))
		{

			struct passwd *pw = getpwuid(getuid());

			username = pw->pw_name;

			printf("(%s) $ elmo ", username);
		}
		free(line);
		free_args(args);

		if (status == -1)
			break;
	}

	return (0);
}
