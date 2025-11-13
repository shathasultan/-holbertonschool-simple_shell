#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

ssize_t my_getline(char **lineptr, size_t *n);  /* declare the function */

int main(void)
{
    char *line = NULL;
    size_t n = 0;
    ssize_t read;

    while ((read = my_getline(&line, &n)) != -1)
    {
        write(STDOUT_FILENO, "You typed: ", 11);
        write(STDOUT_FILENO, line, read);
    }

    free(line);
    return 0;
}
