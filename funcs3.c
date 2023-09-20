#include "shell.h"

/**
 * find_builtin - builtin command
 *
 * @x: info struct
 *
 * Return: -1, 0, -2, 1
 */
int find_builtin(info_t *x)
{
	int i, br = -1;
	builtin_table y[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (i = 0; y[i].type; i++)
		if (_strcmp(x->argv[0], y[i].type) == 0)
		{
			x->line_count++;
			br = y[i].func(x);
			break;
		}
	return (br);
}

/**
 * fork_cmd - fork cmd
 * 
 * @x: info struct
 *
 * Return: void
 */
void fork_cmd(info_t *x)
{
	pid_t y;

	y = fork();
	if (y == -1)
	{
		perror("Error:");
		return;
	}
	if (y == 0)
	{
		if (execve(x->path, x->argv, get_environ(x)) == -1)
		{
			free_info(x, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(x->status));
		if (WIFEXITED(x->status))
		{
			x->status = WEXITSTATUS(x->status);
			if (x->status == 126)
				print_error(x, "Permission denied\n");
		}
	}
}

/**
 * find_cmd - find comd
 *
 * @x: info struct
 *
 * Return: void
 */
void find_cmd(info_t *x)
{
	char *path = NULL;
	int i, l;

	x->path = x->argv[0];
	if (x->linecount_flag == 1)
	{
		x->line_count++;
		x->linecount_flag = 0;
	}
	for (i = 0, l = 0; x->arg[i]; i++)
		if (!is_delim(x->arg[i], " \t\n"))
			l++;
	if (!l)
		return;

	path = find_path(x, _getenv(x, "PATH="), x->argv[0]);
	if (path)
	{
		x->path = path;
		fork_cmd(x);
	}
	else
	{
		if ((interactive(x) || _getenv(x, "PATH=")
			|| x->argv[0][0] == '/') && is_cmd(x, x->argv[0]))
			fork_cmd(x);
		else if (*(x->arg) != '\n')
		{
			x->status = 127;
			print_error(x, "not found\n");
		}
	}
}

/**
 * hsh - shell loop
 *
 * @x: info struct
 * @av: argument vector
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hsh(info_t *x, char **av)
{
	ssize_t y = 0;
	int z = 0;

	while (y != -1 && z != -2)
	{
		clear_info(x);
		if (interactive(x))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		y = get_input(x);
		if (y != -1)
		{
			set_info(x, av);
			z = find_builtin(x);
			if (z == -1)
				find_cmd(x);
		}
		else if (interactive(x))
			_putchar('\n');
		free_info(x, 0);
	}
	write_history(x);
	free_info(x, 1);
	if (!interactive(x) && x->status)
		exit(x->status);
	if (z == -2)
	{
		if (x->err_num == -1)
			exit(x->status);
		exit(x->err_num);
	}
	return (z);
}

/**
 * set_info - initializes info_t
 *
 * @x: info struct
 * @av: argument vector
 *
 * Return: void
 */
void set_info(info_t *x, char **av)
{
	int i = 0;

	x->fname = av[0];
	if (x->arg)
	{
		x->argv = strtow(x->arg, " \t");
		if (!x->argv)
		{

			x->argv = malloc(sizeof(char *) * 2);
			if (x->argv)
			{
				x->argv[0] = _strdup(x->arg);
				x->argv[1] = NULL;
			}
		}
		for (i = 0; x->argv && x->argv[i]; i++)
			;
		x->argc = i;

		replace_alias(x);
		replace_vars(x);
	}
}

