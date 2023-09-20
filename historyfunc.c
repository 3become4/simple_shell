#include "shell.h"

/**
 * get_history_file - gets history file
 *
 * @x: info struct
 *
 * Return: history file
 */

char *get_history_file(info_t *x)
{
	char *buf, *y;

	y = _getenv(x, "HOME=");
	if (!y)
		return (NULL);
	buf = malloc(sizeof(char) * (_strlen(y) + _strlen(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_strcpy(buf, y);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE);
	return (buf);
}

/**
 * read_history - reads history file
 *
 * @x: info struct
 *
 * Return: histcount
 */
int read_history(info_t *x)
{
	int i, l = 0, lc = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_history_file(x);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			build_history_list(x, buf + l, lc++);
			l = i + 1;
		}
	if (l != i)
		build_history_list(x, buf + l, lc++);
	free(buf);
	x->histcount = lc;
	while (x->histcount-- >= HIST_MAX)
		delete_node_at_index(&(x->history), 0);
	renumber_history(x);
	return (x->histcount);
}

/**
 * write_history - creates history file
 *
 * @x: info struct
 *
 * Return: 1
 */
int write_history(info_t *x)
{
	ssize_t fd;
	char *y = get_history_file(x);
	list_t *n = NULL;

	if (!y)
		return (-1);

	fd = open(y, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(y);
	if (fd == -1)
		return (-1);
	for (n = x->history; n; n = n->next)
	{
		_putsfd(n->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}



/**
 * build_history_list - add to history list
 *
 * @x: info struct
 * @buf: buffer
 * @lc: history linecount
 *
 * Return: 0
 */
int build_history_list(info_t *x, char *buf, int lc)
{
	list_t *node = NULL;

	if (x->history)
		node = x->history;
	add_node_end(&node, buf, lc);

	if (!x->history)
		x->history = node;
	return (0);
}

/**
 * renumber_history - renumbers history list
 *
 * @x: info struct
 *
 * Return: new histcount
 */
int renumber_history(info_t *x)
{
	list_t *n = x->history;
	int i = 0;

	while (n)
	{
		n->num = i++;
		n = n->next;
	}
	return (x->histcount = i);
}