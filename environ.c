#include "shell.h"

/**
 *_myenv - Prints the current environment
 *@vc: Structure containing potential arguments,used to
 *maintain constant function prototype.
 *Return: always 0
 */

int _myenv(info_t *vc)
{
	print_list_str(vc->env);
	return (0);
}

/**
 *_getenv - Gets the value of an environ variable
 *@we: Structure containing potential arguments,used to maintain
 *@do: env var name
 *Return: the value
 */

char *_getenv(info_t *we, const char *do)
{
	list_t *de = we->env;
	char *f;

	while (de)
	{
		f = starts_with(de->str, do);
		if (f && *f)
			return (f);
		de = de->next;
	}
	return (NULL);
}

/**
 *_mysetenv - Initialize a new environment variable
 *modify an existing one
 *@fa: Structure containing potential arguments,used to maintain
 *constant function prototype
 *Return: always 0
 */

int _mysetenv(info_t *fa)
{
	if (fa->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(fa, fa->argv[1], fa->argv[2]))
		return (0);
	return (1);
}

/**
 *_myunsetenv - Remove an environment variable
 *@ra: Structure containing potential arguments,used to
 *maintain constant function prototype.
 * Return: Always 0
 */

int _myunsetenv(info_t *ra)
{
	int s;

	if (ra->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (s = 1; s <= ra->argc; s++)
		_unsetenv(ra, ra->argv[s]);
	return (0);
}

/**
 *populate_env_list - Populates env linked list
 *@qe: Structure containing potential arguments,used to
 *maintain constant function prototype
 *Return: always 0
 */

int populate_env_list(info_t *qe)
{
	list_t *nd = NULL;
	size_t t;

	for (t = 0; environ[t]; t++)
		add_node_end(&nd, environ[t], 0);
	qe->env = nd;
	return (0);
}