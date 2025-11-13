#include <stdlib.h>
#include <unistd.h>

#define BUF_SIZE 1024

ssize_t my_getline(char **lineptr, size_t *n)
{
    static char buf[BUF_SIZE];
    static size_t pos = 0;
    static size_t len = 0;
    ssize_t i = 0;  /* changed to signed */
    char *line;
    ssize_t j;      /* declare outside loop for C90 */

    if (!lineptr || !n)
        return -1;

    if (*lineptr == NULL || *n == 0)
    {
        *n = 128;
        *lineptr = malloc(*n);
        if (!*lineptr)
            return -1;
    }

    line = *lineptr;

    while (1)
    {
        if (pos >= len)
        {
            len = read(STDIN_FILENO, buf, BUF_SIZE);
            if (len <= 0)
                return (i == 0) ? -1 : i;
            pos = 0;
        }

        while (pos < len)
        {
            if ((size_t)(i + 1) >= *n)
            {
                size_t new_size = *n * 2;
                char *tmp = malloc(new_size);
                if (!tmp)
                    return -1;
                for (j = 0; j < i; j++)  /* manual copy */
                    tmp[j] = line[j];
                free(line);
                line = tmp;
                *lineptr = line;
                *n = new_size;
            }

            line[i++] = buf[pos++];
            if (line[i-1] == '\n')
                return i;
        }
    }
}
