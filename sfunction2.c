#include "shell.h"

/**
 * _strdup - duplicate
 *
 * @x: string to duplicate
 *
 * Return: pointer to duplicated string
 */
char *_strdup(const char *x)
{
	int l = 0;
	char *y;

	if (x == NULL)
		return (NULL);
	while (*x++)
		l++;
	y = malloc(sizeof(char) * (l + 1));
	if (!y)
		return (NULL);
	for (l++; l--;)
		y[l] = *--x;
	return (y);
}
/**
 **_strncpy - copies string chars
 *
 *@x: destination
 *@y: source
 *@z: num of chars
 *
 *Return: concatenated string
 */
char *_strncpy(char *x, char *y, int z)
{
	int i, j;
	char *s = x;

	i = 0;
	while (y[i] != '\0' && i < z - 1)
	{
		x[i] = y[i];
		i++;
	}
	if (i < z)
	{
		j = i;
		while (j < z)
		{
			x[j] = '\0';
			j++;
		}
	}
	return (s);
}
/**
 **_strncat - concatenates two strings chars
 *
 *@x: destination
 *@y: source
 *@z: num of chars(bytes)
 *
 *Return: concatenated string
 */
char *_strncat(char *x, char *y, int z)
{
	int i, j;
	char *s = x;

	i = 0;
	j = 0;
	while (x[i] != '\0')
		i++;
	while (y[j] != '\0' && j < z)
	{
		x[i] = y[j];
		i++;
		j++;
	}
	if (j < z)
		x[i] = '\0';
	return (s);
}

/**
 *_puts - puts
 *
 *@x: string
 *
 * Return: void
 */
void _puts(char *x)
{
	int i = 0;

	if (!x)
		return;
	while (x[i] != '\0')
	{
		_putchar(x[i]);
		i++;
	}
}
/**
 * _putchar - putchar
 *
 * @x: character to print
 *
 * Return: On success 1.
 */
int _putchar(char x)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (x == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}
	if (x != BUF_FLUSH)
		buf[i++] = x;
	return (1);
}

