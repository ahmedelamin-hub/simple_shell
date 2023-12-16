#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>
#include <fcntl.h>
#include <dirent.h>
#include <string.h>

#define BUFSIZE 1024

extern char **environ;

char *get_line(void);
char **split_line(char *line);
int execute_cmd(char **args);
int built_in_cmd(char **args);
int change_dir(char **args);
int show_env(void);
int exit_shell(char **args);
char *get_env(const char *name);
int set_env(char **args);
int unset_env(char **args);

char *find_cmd(const char *cmd);
int is_dir(const char *path);
char *update_path(char *cwd, char *new_dir);
void free_args(char **args);

#endif /* SHELL_H */

