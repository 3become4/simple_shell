#include "shell.h"

/**
 * clear_info - clear info_t
 *
 * @x: info struct
 *
 * Return: void
 */
void clear_info(info_t *x)
{
	x->arg = NULL;
	x->argv = NULL;
	x->path = NULL;
	x->argc = 0;
}



/**
 * free_info - frees info_t
 *
 * @x: info struct
 * @y: ture or false
 *
 * Return: void
 */
void free_info(info_t *x, int y)
{
	ffree(x->argv);
	x->argv = NULL;
	x->path = NULL;
	if (y)
	{
		if (!x->cmd_buf)
			free(x->arg);
		if (x->env)
			free_list(&(x->env));
		if (x->history)
			free_list(&(x->history));
		if (x->alias)
			free_list(&(x->alias));
		/* bfree(x->environ);
			x->environ = NULL;
		bfree((void **)x->cmd_buf);*/
		if (x->readfd > 2)
			close(x->readfd);
		_putchar(BUF_FLUSH);
	}
}

/**
 * is_cmd - check if cmd
 *
 * @x: info struct
 * @p: path to file
 *
 * Return: 1
 */
int is_cmd(info_t *x, char *p)
{
	struct stat st;

	(void)x;
	if (!p || stat(p, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - duplicates chars
 *
 * @p: PATH
 * @s: index
 * @e: end index
 *
 * Return: buffer pointer
 */
char *dup_chars(char *p, int s, int e)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = s; i < e; i++)
		if (p[i] != ':')
			buf[k++] = p[i];
	buf[k] = 0;
	return (buf);
}

/**
 * find_path - search path
 *
 * @x: info struct
 * @p: PATH
 * @cmd: cmd to find
 *
 * Return: path
 */
char *find_path(info_t *x, char *p, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!p)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(x, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!p[i] || p[i] == ':')
		{
			path = dup_chars(p, curr_pos, i);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(x, path))
				return (path);
			if (!p[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}
