#ifndef MAIN_H
#define MAIN_H

#define MAX_ARGS 1024

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <limits.h>
#include <fcntl.h>

extern char **environ;

/* Shell info structure */
typedef struct shell
{
	char *name;       /* Name of the shell (argv[0]) */
	int cmd_count;    /* Number of commands executed */
	int last_status;  /* Last command exit status */
} t_shell;

/* Core shell functions */
int process_line(char *line, t_shell *info);
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
char *trim_spaces(char *str);
int parse_args(char *line, char **args);

/* Command execution functions */
int exec_cmd(char **args, t_shell *info);
int is_builtin(char **args);
char *find_in_path(char *cmd);
char *_getenv(const char *name);

#endif /* MAIN_H */
