#ifndef SIMPLE_SHELL_H
#define SIMPLE_SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 1024

ssize_t my_getline(char **lineptr, size_t *n, int fd);
void execute_command(char *line);

#endif /* SIMPLE_SHELL_H */
