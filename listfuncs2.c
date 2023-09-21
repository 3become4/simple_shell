#include "shell.h"

/**
 * list_len - length of linked list
 *
 * @x: pointer
 *
 * Return: size of list
 */
size_t list_len(const list_t *x)
{
	size_t i = 0;

	while (x)
	{
		x = x->next;
		i++;
	}
	return (i);
}

/**
 * get_node_index - index of node
 *
 * @x: pointer head
 * @y: pointer node
 *
 * Return: node index
 */
ssize_t get_node_index(list_t *x, list_t *y)
{
	size_t i = 0;

	while (x)
	{
		if (x == y)
			return (i);
		x = x->next;
		i++;
	}
	return (-1);
}
/**
 * delete_node_at_index - deletes node
 *
 * @x: node address
 * @in: index
 *
 * Return: 1 on success, 0 on failure
 */
int delete_node_at_index(list_t **x, unsigned int in)
{
	list_t *n, *pn;
	unsigned int i = 0;

	if (!x || !*x)
		return (0);

	if (!in)
	{
		n = *x;
		*x = (*x)->next;
		free(n->str);
		free(n);
		return (1);
	}
	n = *x;
	while (n)
	{
		if (i == in)
		{
			pn->next = n->next;
			free(n->str);
			free(n);
			return (1);
		}
		i++;
		pn = n;
		n = n->next;
	}
	return (0);
}
/**
 * free_list - free list
 *
 * @x: pointer to list
 *
 * Return: void
 */
void free_list(list_t **x)
{
	list_t *n, *nn, *y;

	if (!x || !*x)
		return;
	y = *x;
	n = y;
	while (n)
	{
		nn = n->next;
		free(n->str);
		free(n);
		n = nn;
	}
	*x = NULL;
}

/**
 * list_to_strings - list of strings
 *
 * @x: pointer
 *
 * Return: list of strings
 */
char **list_to_strings(list_t *x)
{
	list_t *n = x;
	size_t i = list_len(x), j;
	char **ss;
	char *s;

	if (!x || !i)
		return (NULL);
	ss = malloc(sizeof(char *) * (i + 1));
	if (!ss)
		return (NULL);
	for (i = 0; n; n = n->next, i++)
	{
		s = malloc(_strlen(n->str) + 1);
		if (!s)
		{
			for (j = 0; j < i; j++)
				free(ss[j]);
			free(ss);
			return (NULL);
		}

		s = _strcpy(s, n->str);
		ss[i] = s;
	}
	ss[i] = NULL;
	return (ss);
}

