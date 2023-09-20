#include "shell.h"

/**
 * is_chain - tcheck if char is chanined
 *
 * @x: info struct
 * @buf: buffer
 * @p: position in buffer
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int is_chain(info_t *x, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		x->cmd_buf_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		x->cmd_buf_type = CMD_AND;
	}
	else if (buf[j] == ';')
	{
		buf[j] = 0;
		x->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}

/**
 * check_chain - check chain status
 *
 * @x: info struct
 * @buf: buffer
 * @p: position in buf
 * @i: start position in buf
 * @len: length
 *
 * Return: Void
 */
void check_chain(info_t *x, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (x->cmd_buf_type == CMD_AND)
	{
		if (x->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (x->cmd_buf_type == CMD_OR)
	{
		if (!x->status)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*p = j;
}

/**
 * replace_alias -aliace replacement
 *
 * @x: info struct
 *
 * Return: 1
 */
int replace_alias(info_t *x)
{
	int i;
	list_t *n;
	char *p;

	for (i = 0; i < 10; i++)
	{
		n = node_starts_with(x->alias, x->argv[0], '=');
		if (!n)
			return (0);
		free(x->argv[0]);
		p = _strchr(n->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		x->argv[0] = p;
	}
	return (1);
}

/**
 * replace_vars - replace vars
 *
 * @x: info struct
 *
 * Return: 1
 */
int replace_vars(info_t *x)
{
	int i = 0;
	list_t *n;

	for (i = 0; x->argv[i]; i++)
	{
		if (x->argv[i][0] != '$' || !x->argv[i][1])
			continue;

		if (!_strcmp(x->argv[i], "$?"))
		{
			replace_string(&(x->argv[i]),
				_strdup(convert_number(x->status, 10, 0)));
			continue;
		}
		if (!_strcmp(x->argv[i], "$$"))
		{
			replace_string(&(x->argv[i]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		n = node_starts_with(x->env, &x->argv[i][1], '=');
		if (n)
		{
			replace_string(&(x->argv[i]),
				_strdup(_strchr(n->str, '=') + 1));
			continue;
		}
		replace_string(&x->argv[i], _strdup(""));

	}
	return (0);
}

/**
 * replace_string - replaces string
 *
 * @x: old string
 * @y: new string
 *
 * Return: 1
 */
int replace_string(char **x, char *y)
{
	free(*x);
	*x = y;
	return (1);
}
