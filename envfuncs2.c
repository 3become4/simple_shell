#include "shell.h"

/**
 * _myunsetenv - unset env
 *
 * @x: info struct
 *
 *  Return: 0
 */
int _myunsetenv(info_t *x)
{
	int i;

	if (x->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= x->argc; i++)
		_unsetenv(x, x->argv[i]);

	return (0);
}
/**
 * _setenv - new inv
 *
 * @x: info struct
 * @y: env variable
 * @z: new var value
 *
 *  Return: 0
 */
int _setenv(info_t *x, char *y, char *z)
{
	char *buf = NULL;
	list_t *n;
	char *p;

	if (!y || !z)
		return (0);

	buf = malloc(_strlen(y) + _strlen(z) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, y);
	_strcat(buf, "=");
	_strcat(buf, z);
	n = x->env;
	while (n)
	{
		p = starts_with(n->str, y);
		if (p && *p == '=')
		{
			free(n->str);
			n->str = buf;
			x->env_changed = 1;
			return (0);
		}
		n = n->next;
	}
	add_node_end(&(x->env), buf, 0);
	free(buf);
	x->env_changed = 1;
	return (0);
}

/**
 * _unsetenv - unsets env
 *
 * @x: info struct
 * @y: env variable
 *
 *  Return: 1
 */
int _unsetenv(info_t *x, char *y)
{
	list_t *n = x->env;
	size_t i = 0;
	char *p;

	if (!n || !y)
		return (0);

	while (n)
	{
		p = starts_with(n->str, y);
		if (p && *p == '=')
		{
			x->env_changed = delete_node_at_index(&(x->env), i);
			i = 0;
			n = x->env;
			continue;
		}
		n = n->next;
		i++;
	}
	return (x->env_changed);
}
