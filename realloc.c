#include "shell.h"

/**
 *_memset - fills memory with a constant byte
 *@z: the pointer to the memory area
 *@y: the byte to fill *s with
 *@x: the amount of bytes to be filled
 *Return: s a pointer to the memory area s
 */

char *_memset(char *z, char y, unsigned int x)
{
	unsigned int vak;

	for (vak = 0; vak < x; vak++)
		z[vak] = y;
	return (z);
}

/**
 *ffree - Frees a string of strings
 *@b: string of strings
 */

void ffree(char **b)
{
	char **cc = b;

	if (!b)
		return;
	while (*b)
		free(*b++);
	free(cc);
}

/**
 *_realloc - Reallocates a block of memory
 *@pr: pointer to previous malloc'ated block
 *@ol: byte size of previous block
 *@nw: byte size of new block
 *Return: pointer to da ol'block nameen.
 */

void *_realloc(void *pr, unsigned int ol, unsigned int nw)
{
	char *dak;

	if (!pr)
		return (malloc(nw));
	if (!nw)
		return (free(pr), NULL);
	if (nw == ol)
		return (pr);

	dak = malloc(nw);
	if (!dak)
		return (NULL);

	ol = ol < nw ? ol : nw;
	while (ol--)
		dak[ol] = ((char *)pr)[ol];
	free(pr);
	return (dak);
}
