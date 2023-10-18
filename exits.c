#include "shell.h"

/**
 **_strncpy - Copies a string
 *@da: the destination string to be copied to
 *@de: the source string
 *@do: the amount of characters to be copied
 *Return: the concatenated string
 */

char *_strncpy(char *da, char *de, int do)
{
	int x, y;
	char *c = da;

	x = 0;
	while (de[x] != '\0' && x < do - 1)
	{
		da[x] = de[x];
		x++;
	}
	if (x < do)
	{
		y = x;
		while (y < do)
		{
			da[y] = '\0';
			y++;
		}
	}
	return (c);
}

/**
 **_strncat - Concatenates two strings
 *@ce: the first string
 *@ca: the second string
 *@co: the amount of bytes to be maximally used
 *Return: the concatenated string
 */

char *_strncat(char *ce, char *ca, int co)
{
	int a, b;
	char *f = ce;

	a = 0;
	b = 0;
	while (ce[a] != '\0')
		a++;
	while (ca[b] != '\0' && b < co)
	{
		ce[a] = ca[b];
		a++;
		b++;
	}
	if (b < co)
		ce[a] = '\0';
	return (f);
}

/**
 **_strchr - Locates a character in a string
 *@x: the string to be parsed
 *@y: the character to look for
 *Return: s a pointer to the memory area s
 */

char *_strchr(char *x, char y)
{
	do {
		if (*x == y)
			return (x);
	} while (*x++ != '\0');
	return (NULL);
}