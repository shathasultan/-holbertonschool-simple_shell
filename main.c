#include "main.h"

/**
 * main - Entry point of the shell
 * @argc: Argument count
 * @argv: Argument vector
 *
 * Return: Last command status
 */
int main(int argc, char *argv[])
{
	t_shell info;
	char *line = NULL;
	size_t len = 0;

	(void)argc; /* unused */

	info.name = argv[0];
	info.cmd_count = 0;
	info.last_status = 0;

	while (1)
	{
		write(STDOUT_FILENO, "$ ", 2);

		if (_getline(&line, &len, stdin) == -1)
		{
			free(line);
			break;
		}

		line = trim_spaces(line);
		if (*line == '\0')
			continue;

		info.cmd_count++;
		info.last_status = process_line(line, &info);
	}

	free(line);
	return (info.last_status);
}
