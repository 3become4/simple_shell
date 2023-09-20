#include "shell.h"

/**
 * interactive - interactive mode
 * 
 * @x: info struct
 *
 * Return: 1
 */
int interactive(info_t *x)
{
	return (isatty(STDIN_FILENO) && x->readfd <= 2);
}

/**
 *_atoi - string to integer
 *
 *@s: string
 *
 *Return: 0
 */

int _atoi(char *s)
{
	unsigned int x = 0;
	int y = 1;

	do {
		if (*s == '-')
			y *= -1;
		else if (*s >= '0' && *s <= '9')
			x = (x * 10) + (*s - '0');
		else if (x > 0)
			break;
	} while (*s++);
	return (x * y);
}
/**
 * _erratoi - string to integer
 *
 * @x: string
 *
 * Return: 0
 */
int _erratoi(char *x)
{
	int i = 0;
	unsigned long int y = 0;

	if (*x == '+')
		x++; 
	for (i = 0;  x[i] != '\0'; i++)
	{
		if (x[i] >= '0' && x[i] <= '9')
		{
			y *= 10;
			y += (x[i] - '0');
			if (y > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (y);
}
/**
 *_isalpha - checks for alpha
 *
 *@x: num of char
 *
 *Return: 1
 */

int _isalpha(int x)
{
	if (x >= 97 && x <= 122)
		return (1);
	if (x >= 65 && x <= 90)
		return (1);
	return (0);
}

/**
 * is_delim - checks delimeter
 *
 * @x: char
 * @d: delimeter
 *
 * Return: 1
 */
int is_delim(char x, char *d)
{
	while (*d)
		if (*d++ == x)
			return (1);
	return (0);
}