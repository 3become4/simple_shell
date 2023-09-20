#include "shell.h"


/**
 * remove_comments - remve comments
 *
 * @x: string
 *
 * Return: 0
 */
void remove_comments(char *x)
{
	int i;

	for (i = 0; x[i] != '\0'; i++)
		if (x[i] == '#' && (!i || x[i - 1] == ' '))
		{
			x[i] = '\0';
			break;
		}
}
/**
 * print_d - prints decimal
 *
 * @x: input
 * @fd: filedescriptor
 *
 * Return: number of characters printed
 */
int print_d(int x, int fd)
{
	int (*pc)(char) = pc;
	int i, c = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		pc = _eputchar;
	if (x < 0)
	{
		_abs_ = -x;
		pc('-');
		c++;
	}
	else
		_abs_ = x;
	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			pc('0' + current / i);
			c++;
		}
		current %= i;
	}
	pc('0' + current);
	c++;
	return (c);
}
/**
 * print_error - print error
 *
 * @x: info struct
 * @s: error string
 *
 * Return: 0
 */
void print_error(info_t *x, char *s)
{
	_eputs(x->fname);
	_eputs(": ");
	print_d(x->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(x->argv[0]);
	_eputs(": ");
	_eputs(s);
}


/**
 * convert_number - converter function
 *
 * @x: number
 * @b: base
 * @f: flags
 *
 * Return: string
 */
char *convert_number(long int x, int b, int f)
{
	static char *a;
	static char buf[50];
	char sign = 0;
	char *y;
	unsigned long n = x;

	if (!(f & CONVERT_UNSIGNED) && x < 0)
	{
		n = -x;
		sign = '-';

	}
	a = f & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	y = &buf[49];
	*y = '\0';

	do	{
		*--y = a[n % b];
		n /= b;
	} while (n != 0);

	if (sign)
		*--y = sign;
	return (y);
}


