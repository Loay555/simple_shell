#include "shell.h"

/**
 ***strtow - Splits a string into words. Repeat delimiters ignored
 *@zelo: the input string
 *@h: the delimeter string
 *Return: a pointer to an array of strings, or NULL on failure
 */

char **strtow(char *zelo, char *h)
{
	int xe, xo, xa, ma, zad = 0;
	char **meh;

	if (zelo == NULL || zelo[0] == 0)
		return (NULL);
	if (!h)
		h = " ";
	for (xe = 0; zelo[xe] != '\0'; xe++)
		if (!is_delim(zelo[xe], h) && (is_delim(zelo[xe + 1], h) || !zelo[xe + 1]))
			zad++;
	if (zad == 0)
		return (NULL);
	h = malloc((1 + zad) * sizeof(char *));
	if (!h)
		return (NULL);
	for (xe = 0, xo = 0; xo < zad; xo++)
	{
		while (is_delim(zelo[xe], h))
			xe++;
		xa = 0;
		while (!is_delim(zelo[xe + xa], h) && zelo[xe + xa])
			xa++;
		h[xo] = malloc((xa + 1) * sizeof(char));
		if (!h[xo])
		{
			for (xa = 0; xa < xo; xa++)
				free(h[xa]);
			free(h);
			return (NULL);
		}
		for (ma = 0; ma < xa; ma++)
			h[xo][ma] = zelo[xe++];
		h[xo][ma] = 0;
	}
	h[xo] = NULL;
	return (h);
}

/**
 ***strtow2 - Splits a string into words
 *@vest: the input string
 *@gad: the delimeter
 *Return: a pointer to an array of strings, or NULL on failure
 */

char **strtow2(char *vest, char gad)
{
	int xx, yy, zz, nn, mu = 0;
	char **ev;

	if (vest == NULL || vest[0] == 0)
		return (NULL);
	for (xx = 0; vest[xx] != '\0'; xx++)
		if ((vest[xx] != gad && vest[xx + 1] == gad) ||
				    (vest[xx] != gad && !vest[xx + 1]) || vest[xx + 1] == gad)
			mu++;
	if (mu == 0)
		return (NULL);
	ev = malloc((1 + mu) * sizeof(char *));
	if (!ev)
		return (NULL);
	for (xx = 0, yy = 0; yy < mu; yy++)
	{
		while (vest[xx] == gad && vest[xx] != gad)
			xx++;
		zz = 0;
		while (vest[xx + zz] != gad && vest[xx + zz] && vest[xx + zz] != gad)
			zz++;
		ev[yy] = malloc((zz + 1) * sizeof(char));
		if (!ev[yy])
		{
			for (zz = 0; zz < yy; zz++)
				free(ev[zz]);
			free(ev);
			return (NULL);
		}
		for (nn = 0; nn < zz; nn++)
			ev[yy][nn] = vest[xx++];
		ev[yy][nn] = 0;
	}
	ev[yy] = NULL;
	return (ev);
}