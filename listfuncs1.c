#include "shell.h"

/**
 * add_node - node to start of list
 *
 * @x: address to pointer
 * @s: str 
 * @n: index
 *
 * Return: size of list
 */
list_t *add_node(list_t **x, const char *s, int n)
{
	list_t *y;

	if (!x)
		return (NULL);
	y = malloc(sizeof(list_t));
	if (!y)
		return (NULL);
	_memset((void *)y, 0, sizeof(list_t));
	y->n = n;
	if (s)
	{
		y->s = _strdup(s);
		if (!y->s)
		{
			free(y);
			return (NULL);
		}
	}
	y->next = *x;
	*x = y;
	return (y);
}
/**
 * add_node_end - node to end of list
 *
 * @x: address to pointer
 * @s: str 
 * @n: index
 *
 * Return: size of list
 */
list_t *add_node_end(list_t **x, const char *s, int n)
{
	list_t *y, *no;

	if (!x)
		return (NULL);

	no = *x;
	y = malloc(sizeof(list_t));
	if (!y)
		return (NULL);
	_memset((void *)y, 0, sizeof(list_t));
	y->n = n;
	if (s)
	{
		y->s = _strdup(s);
		if (!y->s)
		{
			free(y);
			return (NULL);
		}
	}
	if (no)
	{
		while (no->next)
			no = no->next;
		no->next = y;
	}
	else
		*x = y;
	return (y);
}
/**
 * node_starts_with - node  string starts with
 *
 * @x: list head
 * @y: string
 * @c: character to match
 *
 * Return: matched node
 */
list_t *node_starts_with(list_t *x, char *y, char c)
{
	char *z = NULL;

	while (x)
	{
		z = starts_with(x->str, y);
		if (z && ((c == -1) || (*z == c)))
			return (x);
		x = x->next;
	}
	return (NULL);
}
/**
 * print_list - prints all of a list_t linked list
 *
 * @x: pointer
 *
 * Return: size of list
 */
size_t print_list(const list_t *x)
{
	size_t i = 0;

	while (x)
	{
		_puts(convert_number(x->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(x->str ? x->str : "(nil)");
		_puts("\n");
		x = x->next;
		i++;
	}
	return (i);
}

/**
 * print_list_str - prints the str element of list_t linked list
 *
 * @x: pointer
 *
 * Return: size of list
 */
size_t print_list_str(const list_t *x)
{
	size_t i = 0;

	while (x)
	{
		_puts(x->str ? x->str : "(nil)");
		_puts("\n");
		x = x->next;
		i++;
	}
	return (i);
}