#include "shell.h"

/**
 * _myexit - exits the shell
 *
 * @x: info struct
 *
 *  Return: exit code
 */
int _myexit(info_t *x)
{
	int ec;

	if (x->argv[1])
	{
		ec = _erratoi(x->argv[1]);
		if (ec == -1)
		{
			x->status = 2;
			print_error(x, "Illegal number: ");
			_eputs(x->argv[1]);
			_eputchar('\n');
			return (1);
		}
		x->err_num = _erratoi(x->argv[1]);
		return (-2);
	}
	x->err_num = -1;
	return (-2);
}
/**
 * _myhistory - command history
 *
 * @x: info struct
 *
 *  Return: Always 0
 */
int _myhistory(info_t *x)
{
	print_list(x->history);
	return (0);
}

/**
 * _mycd - changes current directory
 *
 * @x: info struct
 *
 *  Return: Always 0
 */
int _mycd(info_t *x)
{
	char *s, *d, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!x->argv[1])
	{
		d = _getenv(x, "HOME=");
		if (!d)
			chdir_ret = chdir((d = _getenv(x, "PWD=")) ? d : "/");
		else
			chdir_ret = chdir(d);
	}
	else if (_strlex(x->argv[1], "-") == 0)
	{
		if (!_getenv(x, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(x, "OLDPWD=")), _putchar('\n');
		chdir_ret = chdir((d = _getenv(x, "OLDPWD=")) ? d : "/");
	}
	else
		chdir_ret = chdir(x->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(x, "can't cd to ");
		_eputs(x->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(x, "OLDPWD", _getenv(x, "PWD="));
		_setenv(x, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _myhelp - help call
 *
 * @x: info struct
 *
 *  Return: Always 0
 */
int _myhelp(info_t *x)
{
	char **arg_array;

	arg_array = x->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array);
	return (0);
}

