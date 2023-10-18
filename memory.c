#include "shell.h"

/**
 *bfree - Frees a pointer and NULLs the address
 *@sav: address of the pointer to free
 *Return: 1 if freed and otherwise 0
 */

int bfree(void **sav)
{
	if (sav && *sav)
	{
		free(*sav);
		*sav = NULL;
		return (1);
	}
	return (0);

}
