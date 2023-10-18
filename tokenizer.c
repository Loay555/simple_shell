#include "shell.h"

/**
 * **strtow - Splits a string into words Repeat delimiters are ignored
 * @haz: the input string
 * @fak: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **strtow(char *haz, char *fak)
{
	int xavoy, davoy, shakoy, merit, marl = 0;
	char **fendaz;

	if (haz == NULL || haz[0] == 0)
		return (NULL);
	if (!fak)
		fak = " ";
	for (xavoy = 0; haz[xavoy] != '\0'; xavoy++)
		if (!is_delim(haz[xavoy], fak) && (is_delim(haz[xavoy + 1], fak) || !haz[xavoy + 1]))
			marl++;
	if (marl == 0)
		return (NULL);
	fendaz = malloc((1 + marl) * sizeof(char *));
	if (!fendaz)
		return (NULL);
	for (xavoy = 0, davoy = 0; davoy < marl; davoy++)
	{
		while (is_delim(haz[xavoy], fak))
			xavoy++;
		shakoy = 0;
		while (!is_delim(haz[xavoy + shakoy], fak) && haz[xavoy + shakoy])
			shakoy++;
		fendaz[davoy] = malloc((shakoy + 1) * sizeof(char));
		if (!fendaz[davoy])
		{
			for (shakoy = 0; shakoy < davoy; shakoy++)
				free(fendaz[shakoy]);
			free(fendaz);
			return (NULL);
		}
		for (merit = 0; merit < shakoy; merit++)
			fendaz[davoy][merit] = haz[xavoy++];
		fendaz[davoy][merit] = 0;
	}
	fendaz[davoy] = NULL;
	return (fendaz);
}

/**
 * **strtow2 - Splits a string into words
 * @bravo: the input string
 * @chipsy: the delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strtow2(char *bravo, char chipsy)
{
	int sera, gera, kera, zerar, conta = 0;
	char **xapt;

	if (bravo == NULL || bravo[0] == 0)
		return (NULL);
	for (sera = 0; bravo[sera] != '\0'; sera++)
		if ((bravo[sera] != chipsy && bravo[sera + 1] == chipsy) ||
				    (bravo[sera] != chipsy && !bravo[sera + 1]) || bravo[sera + 1] == chipsy)
			conta++;
	if (conta == 0)
		return (NULL);
	xapt = malloc((1 + conta) * sizeof(char *));
	if (!xapt)
		return (NULL);
	for (sera = 0, gera = 0; gera < conta; gera++)
	{
		while (bravo[sera] == chipsy && bravo[sera] != chipsy)
			sera++;
		kera = 0;
		while (bravo[sera + kera] != chipsy && bravo[sera + kera] && bravo[sera + kera] != chipsy)
			kera++;
		xapt[gera] = malloc((kera + 1) * sizeof(char));
		if (!xapt[gera])
		{
			for (kera = 0; kera < gera; kera++)
				free(xapt[kera]);
			free(xapt);
			return (NULL);
		}
		for (zerar = 0; zerar < kera; zerar++)
			xapt[gera][zerar] = bravo[sera++];
		xapt[gera][zerar] = 0;
	}
	xapt[gera] = NULL;
	return (xapt);
}
