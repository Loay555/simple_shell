#include "shell.h"

/**
 *_strcpy - Copies a string
 *@xex: the destination
 *@mix: the source
 *Return: pointer to destination
 */

char *_strcpy(char *xex, char *mix)
{
	int vee = 0;

	if (xex == mix || mix == 0)
		return (xex);
	while (mix[vee])
	{
		xex[vee] = mix[vee];
		vee++;
	}
	xex[vee] = 0;
	return (xex);
}

/**
 *_strdup - Duplicates a string
 *@hago: the string to duplicate
 *Return: pointer to the duplicated string
 */

char *_strdup(const char *hago)
{
	int mazo = 0;
	char *mid;

	if (hago == NULL)
		return (NULL);
	while (*hago++)
		mazo++;
	mid = malloc(sizeof(char) * (mazo + 1));
	if (!mid)
		return (NULL);
	for (mazo++; mazo--;)
		mid[mazo] = *--hago;
	return (mid);
}

/**
 *_puts - Prints an input string
 *@jar: the string to be printed
 * Return: nothing
 */

void _puts(char *jar)
{
	int daka = 0;

	if (!jar)
		return;
	while (jar[daka] != '\0')
	{
		_putchar(jar[daka]);
		daka++;
	}
}

/**
 *_putchar - Writes the character c to stdout
 *@u: The character to print
 *Return: On success 1
 *On error -1 is returned and errno is set appropriately
 */

int _putchar(char u)
{
	static int re;
	static char buf[WRITE_BUF_SIZE];

	if (u == BUF_FLUSH || re >= WRITE_BUF_SIZE)
	{
		write(1, buf, re);
		re = 0;
	}
	if (u != BUF_FLUSH)
		buf[re++] = u;
	return (1);
}
