#include "shell.h"

/**
 * input_buf - input buffers commands
 *
 * @x: info struct
 * @buf: address of buffer
 * @l: address of len var
 *
 * Return: bytes
 */
ssize_t input_buf(info_t *x, char **buf, size_t *l)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*l)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		r = getline(buf, &len_p, stdin);
#else
		r = _getline(x, buf, &len_p);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0';
				r--;
			}
			x->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(x, *buf, x->histcount++);
			{
				*l = r;
				x->cmd_buf = buf;
			}
		}
	}
	return (r);
}

/**
 * get_input - gets input lines
 *
 * @x: info struct
 *
 * Return: bytes
 */
ssize_t get_input(info_t *x)
{
	static char *buf;
	static size_t i, j, l;
	ssize_t y = 0;
	char **buf_p = &(x->arg), *p;

	_putchar(BUF_FLUSH);
	y = input_buf(x, &buf, &l);
	if (y == -1)
		return (-1);
	if (l)
	{
		j = i;
		p = buf + i;

		check_chain(x, buf, &j, i, l);
		while (j < l)
		{
			if (is_chain(x, buf, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= l)
		{
			i = l = 0;
			x->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p;
		return (_strlen(p));
	}

	*buf_p = buf;
	return (y);
}

/**
 * read_buf - read buffer
 *
 * @x: info struct
 * @buf: buffer
 * @i: size
 *
 * Return: r
 */
ssize_t read_buf(info_t *x, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(x->readfd, buf, READ_BUF_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * _getline - next line from STDIN
 *
 * @x: info struct
 * @ptr: buff pointer
 * @l: size
 *
 * Return: line
 */
int _getline(info_t *x, char **ptr, size_t *l)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t y;
	ssize_t z = 0, li = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && l)
		li = *l;
	if (i == len)
		i = len = 0;

	z = read_buf(x, buf, &len);
	if (z == -1 || (z == 0 && len == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	y = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, li, li ? li + y : y + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (li)
		_strncat(new_p, buf + i, y - i);
	else
		_strncpy(new_p, buf + i, y - i + 1);

	li += y - i;
	i = y;
	p = new_p;

	if (l)
		*l = li;
	*ptr = p;
	return (li);
}

/**
 * sigintHandler - block ctrl-C
 *
 * @x: signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int x)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}

