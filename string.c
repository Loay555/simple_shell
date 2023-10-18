#include "shell.h"

/**
 *_strlen - Returns the length of a string
 *@e: the string whose length to check
 *Return: integer length of string
 */

int _strlen(char *e)
{
	int faf = 0;

	if (!e)
		return (0);

	while (*e++)
		faf++;
	return (faf);
}

/**
 *_strcmp - Performs lexicogarphic comparison of two strangs.
 *@zaw: the first strang
 *@zam: the second strang
 *Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 */

int _strcmp(char *zaw, char *zam)
{
	while (*zaw && *zam)
	{
		if (*zaw != *zam)
			return (*zaw - *zam);
		zaw++;
		zam++;
	}
	if (*zaw == *zam)
		return (0);
	else
		return (*zaw < *zam ? -1 : 1);
}

/**
 *starts_with - Checks if needle starts with haystack
 *@zack: string to search
 *@sock: the substring to find
 *Return: address of next char of haystack or NULL
 */

char *starts_with(const char *zack, const char *sock)
{
	while (*sock)
		if (*sock++ != *zack++)
			return (NULL);
	return ((char *)zack);
}

/**
 *_strcat - Concatenates two strings
 *@ts: the destination buffer
 *@cr: the source buffer
 *Return: pointer to destination buffer
 */

char *_strcat(char *ts, char *cr)
{
	char *ret = ts;

	while (*ts)
		ts++;
	while (*cr)
		*ts++ = *cr++;
	*ts = *cr;
	return (ret);
}
