#include "main.h"

/**
 * _getline - Custom getline implementation
 * @lineptr: Pointer to store the read line
 * @n: Pointer to buffer size
 * @stream: Input stream (stdin)
 *
 * Return: Number of characters read, or -1 on failure/EOF
 */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
	static char buffer[1024];
	static size_t buf_pos;
	static ssize_t buf_len;
	size_t line_len = 0;
	char *line = NULL;
	char c;

	if (!lineptr || !n || !stream)
		return (-1);

	while (1)
	{
		if ((ssize_t)buf_pos >= buf_len)
		{
			buf_len = read(fileno(stream), buffer, sizeof(buffer));
			buf_pos = 0;
			if (buf_len == 0)
				return (line_len ? (ssize_t)line_len : -1);
			if (buf_len < 0)
				return (-1);
		}

		c = buffer[buf_pos++];

		if (line_len + 1 >= *n)
		{
			size_t new_size = (*n == 0 ? 128 : *n * 2);
			char *new_line = realloc(line, new_size);
			if (!new_line)
			{
				free(line);
				return (-1);
			}
			line = new_line;
			*n = new_size;
		}

		line[line_len++] = c;
		if (c == '\n')
			break;
	}

	line[line_len] = '\0';
	*lineptr = line;
	return ((ssize_t)line_len);
}

/**
 * trim_spaces - Remove leading/trailing spaces
 */
char *trim_spaces(char *str)
{
	char *end;

	while (*str == ' ' || *str == '\t' || *str == '\n')
		str++;

	if (*str == '\0')
		return (str);

	end = str + strlen(str) - 1;

	while (end > str && (*end == ' ' || *end == '\t' || *end == '\n'))
		end--;

	*(end + 1) = '\0';
	return (str);
}

/**
 * parse_args - Tokenizes input line
 */
int parse_args(char *line, char **args)
{
	int i = 0;
	char *token = strtok(line, " \t\n");

	while (token && i < 63)
	{
		args[i++] = token;
		token = strtok(NULL, " \t\n");
	}
	args[i] = NULL;
	return (i);
}
