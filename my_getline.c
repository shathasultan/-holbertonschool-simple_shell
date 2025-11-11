#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

char *my_getline(void)
{
    static char buffer[BUFFER_SIZE];
    static ssize_t buf_pos = 0;
    static ssize_t buf_len = 0;

    char *line = NULL;
    size_t line_len = 0;
    ssize_t i;

    while (1)
    {
        if (buf_pos >= buf_len)
        {
            buf_len = read(STDIN_FILENO, buffer, BUFFER_SIZE);
            buf_pos = 0;
            if (buf_len <= 0)
                return (line_len > 0 ? line : NULL);
        }

        for (i = buf_pos; i < buf_len; i++)
        {
            char c = buffer[i];
            char *tmp = realloc(line, line_len + 2);
            if (!tmp)
            {
                free(line);
                return NULL;
            }
            line = tmp;
            line[line_len++] = c;
            if (c == '\n')
            {
                buf_pos = i + 1;
                line[line_len] = '\0';
                return line;
            }
        }
        buf_pos = buf_len;
    }
}
