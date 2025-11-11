#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char *my_getline(void); /* Prototype from my_getline.c */

int main(void)
{
    char *line;

    while (1)
    {
        write(1, "$ ", 2); // Prompt

        line = my_getline();
        if (!line) // Ctrl+D
            break;

        // Remove trailing newline
        if (line[strlen(line) - 1] == '\n')
            line[strlen(line) - 1] = '\0';

        if (strlen(line) == 0)
        {
            free(line);
            continue;
        }

        printf("You typed: %s\n", line);
        free(line);
    }

    write(1, "\n", 1);
    return 0;
}
