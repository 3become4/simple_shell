#include "shell.h"

/**
 * _getenv - get environment
 *
 * @x: info struct
 * @n: env name
 *
 * Return: env value
 */
char *_getenv(info_t *x, const char *n)
{
	list_t *node = x->env;
	char *y;

	while (node)
	{
		y = starts_with(node->str, n);
		if (y && *y)
			return (y);
		node = node->next;
	}
	return (NULL);
}
/**
 * get_environ - get string of environ
 *
 * @x: info struct
 *
 * Return: 0
 */
char **get_environ(info_t *x)
{
	if (!x->environ || x->env_changed)
	{
		x->environ = list_to_strings(x->env);
		x->env_changed = 0;
	}

	return (x->environ);
}

/**
 * _myenv - current environment
 *
 * @x: info struct
 *
 * Return: 0
 */
int _myenv(info_t *x)
{
	print_list_str(x->env);
	return (0);
}

/**
 * populate_env_list - populates env list
 *
 * @x: info struct
 *
 * Return: 0
 */
int populate_env_list(info_t *x)
{
	list_t *y = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&y, environ[i], 0);
	x->env = y;
	return (0);
}

/**
 * _mysetenv - new environment
 *
 * @x: info struct
 *
 *  Return: 0
 */
int _mysetenv(info_t *x)
{
	if (x->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(x, x->argv[1], x->argv[2]))
		return (0);
	return (1);
}