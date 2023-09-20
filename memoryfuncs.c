#include "shell.h"

/**
 **_memset - fills memory with constant byte
 *
 *@x: pointer to memory
 *@y: byte
 *@z: bytes to fill
 *
 *Return: pointer memory
 */
char *_memset(char *x, char y, unsigned int z)
{
	unsigned int i;

	for (i = 0; i < z; i++)
		x[i] = y;
	return (x);
}
/**
 * _realloc - reallocates memory
 *
 * @x: pointer malloc
 * @os: old byte size
 * @ns: new byte size
 *
 * Return: pointer memory
 */
void *_realloc(void *x, unsigned int os, unsigned int ns)
{
	char *p;

	if (!x)
		return (malloc(ns));
	if (!ns)
		return (free(x), NULL);
	if (ns == os)
		return (x);

	p = malloc(ns);
	if (!p)
		return (NULL);

	os = os < ns ? os : ns;
	while (os--)
		p[os] = ((char *)x)[os];
	free(x);
	return (p);
}

/**
 * ffree - frees strings
 *
 * @x: strings
 *
 * Return: void
 */
void ffree(char **x)
{
	char **y = x;

	if (!x)
		return;
	while (*x)
		free(*x++);
	free(y);
}

/**
 * bfree - free pointer and NULL address
 *
 * @x: pointer to free
 *
 * Return: 1 if free
 */
int bfree(void **x)
{
	if (x && *x)
	{
		free(*x);
		*x = NULL;
		return (1);
	}
	return (0);
}