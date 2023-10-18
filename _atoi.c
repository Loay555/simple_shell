#include "shell.h"

/**
 *interactive - Returns true if shell is interactive mode
 *@he: struct address
 *Return: 1 if interactive mode 0 otherwise
 */

int interactive(info_t *he)
{
	return (isatty(STDIN_FILENO) && he->readfd <= 2);
}

/**
 *is_delim - Checks if character is a delimeter
 *@e: the char to check
 *@solo: the delimeter string
 *Return: 1 if true 0 if false
 */

int is_delim(char e, char *solo)
{
	while (*solo)
		if (*solo++ == e)
			return (1);
	return (0);
}

/**
 *_isalpha - Checks for alphabetic character
 *@b: The character to input
 *Return: 1 if c is alphabetic 0 otherwise
 */

int _isalpha(int b)
{
	if ((b >= 'a' && b <= 'z') || (b >= 'A' && b <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *_atoi - converts a string to an integer
 *@x: the string to be converted
 *Return: 0 if no numbers in string, converted number otherwise
 */

int _texttoi(char *x)
{
	int a, n = 1, z = 0, v;
	unsigned int lt = 0;

	for (a = 0; x[a] != '\0' && z != 2; a++)
	{
		if (x[a] == '-')
			n *= -1;
		if (x[a] >= '0' && x[a] <= '9')
		{
			z = 1;
			lt *= 10;
			lt += (x[a] - '0');
		}
		else if (z == 1)
			z = 2;
	}
	if (n == -1)
		v = -lt;
	else
		v = lt;
	return (v);

}