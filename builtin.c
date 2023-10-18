#include "shell.h"

/**
 *_myexit - Exits the shell
 *@e: Structure containing potential arguments. Used to maintain
 *constant function prototype.
 *Return: exits with a given exit status
 *0 if info argv[0] != "exit"
 */

int _myexit(info_t *e)
{
	int ab;

	if (e->argv[1]) /* If there is an exit arguement */
	{
		ab = _erratoi(e->argv[1]);
		if (ab == -1)
		{
			e->status = 2;
			print_error(e, "Illegal number: ");
			_eputs(e->argv[1]);
			_eputchar('\n');
			return (1);
		}
		e->err_num = _erratoi(e->argv[1]);
		return (-2);
	}
	e->err_num = -1;
	return (-2);
}

/**
 *_mycd - Changes the current directory of the process
 *@e: Structure containing potential arguments Used to maintain
 *constant function prototype
 *Return: Always 0
 */

int _mycd(info_t *e)
{
	char *m, *n, buffer[1024];
	int cd;

	m = getcwd(buffer, 1024);
	if (!m)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!e->argv[1])
	{
		n = _getenv(e, "HOME=");
		if (!n)
			cd = /* TODO: what should this be? */
				chdir((n = _getenv(e, "PWD=")) ? n : "/");
		else
			cd = chdir(n);
	}
	else if (_strcmp(e->argv[1], "-") == 0)
	{
		if (!_getenv(e, "OLDPWD="))
		{
			_puts(m);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(e, "OLDPWD=")), _putchar('\n');
		cd = /* TODO: what should this be? */
			chdir((n = _getenv(e, "OLDPWD=")) ? n : "/");
	}
	else
		cd = chdir(e->argv[1]);
	if (cd == -1)
	{
		print_error(e, "can't cd to ");
		_eputs(e->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(e, "OLDPWD", _getenv(e, "PWD="));
		_setenv(e, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 *_myhelp - Changes the current directory of the process
 *@e: Structure containing potential arguments. Used to maintain
 *constant function prototype.
 *Return: Always 0
 */

int _myhelp(info_t *e)
{
	char **tr;

	tr = e->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*tr); /* temp att_unused workaround */
	return (0);
}