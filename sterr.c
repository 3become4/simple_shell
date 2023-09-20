#include "shell.h"


/**
 * _putfd - write char to filedescriptor
 *
 * @x: char
 * @fd: filedescriptor
 *
 * Return: 1
 */
int _putfd(char x, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (x == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (x != BUF_FLUSH)
		buf[i++] = x;
	return (1);
}

/**
 *_putsfd - prints string
 *
 * @x: string
 * @fd: filedescriptor
 *
 * Return: number of chars
 */
int _putsfd(char *x, int fd)
{
	int i = 0;

	if (!x)
		return (0);
	while (*x)
	{
		i += _putfd(*x++, fd);
	}
	return (i);
}

/**
 * _eputchar - write to stderr
 *
 * @x: char
 *
 * Return: 1
 */
int _eputchar(char x)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (x == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (x != BUF_FLUSH)
		buf[i++] = x;
	return (1);
}

/**
 *_eputs - prints string
 *
 * @x: string
 *
 * Return: void
 */
void _eputs(char *x)
{
	int i = 0;

	if (!x)
		return;
	while (x[i] != '\0')
	{
		_eputchar(x[i]);
		i++;
	}
}

