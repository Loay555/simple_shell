#include "shell.h"

/**
 *_erratoi - Converts a string to an integer
 *@x: the string to be converted
 *Return: 0 if no numbers in string converted number
 *otherwise -1 on error
 */

int _erratoi(char *x)
{
	int y = 0;
	unsigned long int tlu = 0;

	if (*x == '+')
		x++;  /* TODO: why does this make main return 255? */
	for (y = 0;  x[y] != '\0'; y++)
	{
		if (x[y] >= '0' && x[y] <= '9')
		{
			tlu *= 10;
			tlu += (x[y] - '0');
			if (tlu > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (tlu);
}

/**
 *print_error - Prints an error message
 *@fa: the parameter & return info struct
 *@sr: string containing specified error type
 *Return: 0 if no numbers in string and converted number
 *otherwise -1 on error
 */

void print_error(info_t *fa, char *sr)
{
	_eputs(fa->fname);
	_eputs(": ");
	print_d(fa->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(fa->argv[0]);
	_eputs(": ");
	_eputs(sr);
}

/**
 *print_d - Function prints a decimal (integer) number (base 10)
 *@ni: the input
 *@na: the filedescriptor to write to
 *Return: number of characters printed
 */

int print_d(int ni, int na)
{
	int (*__putchar)(char) = _putchar;
	int c, u = 0;
	unsigned int _abs_, current;

	if (na == STDERR_FILENO)
		__putchar = _eputchar;
	if (ni < 0)
	{
		_abs_ = -ni;
		__putchar('-');
		u++;
	}
	else
		_abs_ = ni;
	current = _abs_;
	for (c = 1000000000; c > 1; c /= 10)
	{
		if (_abs_ / c)
		{
			__putchar('0' + current / c);
			u++;
		}
		current %= c;
	}
	__putchar('0' + current);
	u++;
	return (u);
}

/**
 * convert_number - Converter function a clone of itoa
 *@no: number
 *@be: base
 *@gs: argument flags
 *Return: string
 */

char *convert_number(long int no, int be, int gs)
{
	static char *ya;
	static char buffer[50];
	char gi = 0;
	char *rt;
	unsigned long z = no;

	if (!(gs & CONVERT_UNSIGNED) && no < 0)
	{
		z = -no;
		gi = '-';
	}
	ya = gs & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	rt = &buffer[49];
	*rt = '\0';
	do	{
		*--rt = ya[z % be];
		z /= be;
	} while (z != 0);
	if (gi)
		*--rt = gi;
	return (rt);
}

/**
 *remove_comments - Function replaces first instance of '#' with '\0'
 *@ta: address of the string to modify
 *Return: always 0
 */

void remove_comments(char *ta)
{
	int v;

	for (v = 0; ta[v] != '\0'; v++)
		if (ta[v] == '#' && (!v || ta[v - 1] == ' '))
		{
			ta[v] = '\0';
			break;
		}
}
