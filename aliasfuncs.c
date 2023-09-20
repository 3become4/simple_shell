#include "shell.h"


/**
 * unset_alias - unsets alias
 *
 * @x: info struct
 * @s:  string
 *
 * Return: Always 0 on success
 */
int unset_alias(info_t *x, char *s)
{
	char *y, z;
	int rt;

	y = _strchr(s, '=');
	if (!y)
		return (1);
	z = *y;
	*y = 0;
	rt = delete_node_at_index(&(x->alias),
		get_node_index(x->alias, node_starts_with(x->alias, s, -1)));
	*y = z;
	return (rt);
}

/**
 * set_alias - sets alias
 *
 * @x: info struct
 * @s:  string
 *
 * Return: Always 0 on success
 */
int set_alias(info_t *x, char *s)
{
	char *p;

	p = _strchr(s, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(x, s));

	unset_alias(x, s);
	return (add_node_end(&(x->alias), s, 0) == NULL);
}

/**
 * print_alias - print alias
 *
 * @x: alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_t *x)
{
	char *c = NULL, *y = NULL;

	if (x)
	{
		c = _strchr(x->str, '=');
		for (y = x->str; y <= c; y++)
			_putchar(*y);
		_putchar('\'');
		_puts(c + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - gets the aliases
 *
 * @x: info struct
 *
 *  Return: Always 0
 */
int _myalias(info_t *x)
{
	int i = 0;
	char *c = NULL;
	list_t *node = NULL;

	if (x->argc == 1)
	{
		node = x->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; x->argv[i]; i++)
	{
		c = _strchr(x->argv[i], '=');
		if (c)
			set_alias(x, x->argv[i]);
		else
			print_alias(node_starts_with(x->alias, x->argv[i], '='));
	}

	return (0);
}
