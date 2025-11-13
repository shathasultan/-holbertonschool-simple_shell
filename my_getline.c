#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

ssize_t my_getline(char **lineptr, size_t *n)
{
    static char buffer[BUFFER_SIZE];
    static size_t pos = 0, len = 0;
    ssize_t i = 0;  // <-- changed to signed
    char *line = NULL;

    if (!lineptr || !n)
        return -1;

    line = *lineptr;
    if (!line) {
        *n = 128;
        line = malloc(*n);
        if (!line)
            return -1;
    }

    while (1)
    {
        if (pos >= len)
        {
            len = read(STDIN_FILENO, buffer, BUFFER_SIZE);
            pos = 0;
            if (len <= 0)
                return (i > 0) ? i : -1;
        }

        char c = buffer[pos++];
        if (i + 1 >= (ssize_t)*n)  // cast to ssize_t
        {
            *n *= 2;
            line = realloc(line, *n);
            if (!line)
                return -1;
        }

        line[i++] = c;

        if (c == '\n')
            break;
    }

    line[i] = '\0';
    *lineptr = line;
    return i;
}
