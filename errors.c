#include "shell.h"

/**
 *_eputs - Prints an input string
 *@es: the string to be printed
 * Return: empty
 */

void _eputs(char *es)
{
	int ga = 0;

	if (!es)
		return;
	while (es[ga] != '\0')
	{
		_eputchar(es[ga]);
		ga++;
	}
}

/**
 *_eputchar - Writes the character c to stderr
 *@k: The character to print
 *Return: On success 1
 *On error -1 is returned, and errno is set appropriately.
 */

int _eputchar(char k)
{
	static int x;
	static char buf[WRITE_BUF_SIZE];

	if (k == BUF_FLUSH || x >= WRITE_BUF_SIZE)
	{
		write(2, buf, x);
		x = 0;
	}
	if (k != BUF_FLUSH)
		buf[x++] = k;
	return (1);
}

/**
 *_putfd - Writes the character c to given fd
 *@j: The character to print
 *@d: The filedescriptor to write to
 *Return: On success 1
 *On error -1 is returned and errno is set appropriately
 */

int _putfd(char j, int d)
{
	static int y;
	static char buf[WRITE_BUF_SIZE];

	if (j == BUF_FLUSH || y >= WRITE_BUF_SIZE)
	{
		write(d, buf, y);
		y = 0;
	}
	if (j != BUF_FLUSH)
		buf[y++] = j;
	return (1);
}

/**
 *_putsfd - Prints an input string
 *@buf: the string to be printed
 *@but: the filedescriptor to write to
 *Return: the number of chars put
 */

int _putsfd(char *buf, int but)
{
	int y = 0;

	if (!buf)
		return (0);
	while (*buf)
	{
		y += _putfd(*buf++, but);
	}
	return (y);
}