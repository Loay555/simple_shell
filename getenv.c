#include "shell.h"

/**
 *get_environ - Returns the string array copy of our environ
 *@fn: Structure containing potential arguments,used to
 *maintain constant function prototype.
 *Return: Always 0
 */

char **get_environ(info_t *fn)
{
	if (!fn->environ || fn->env_changed)
	{
		fn->environ = list_to_strings(fn->env);
		fn->env_changed = 0;
	}
	return (fn->environ);
}

/**
 *_unsetenv - Remove an environment variable
 *@ni: Structure containing potential arguments,used to
 *maintain constant function prototype.
 *@na: the string env var property
 *Return: 1 on delete and 0 otherwise
 */

int _unsetenv(info_t *ni, char *na)
{
	list_t *dah = ni->env;
	size_t va = 0;
	char *vy;

	if (!dah || !na)
		return (0);

	while (dah)
	{
		vy = starts_with(dah->str, na);
		if (vy && *vy == '=')
		{
			ni->env_changed = delete_node_at_index(&(ni->env), va);
			va = 0;
			dah = ni->env;
			continue;
		}
		dah = dah->next;
		va++;
	}
	return (ni->env_changed);
}

/**
 *_setenv - Initialize a new environment variable
 *or modify an existing one
 *@of: Structure containing potential arguments,used to
 *maintain constant function prototype
 *@rv: the string env var property
 *@eu: the string env var value
 *Return: Always 0
 */

int _setenv(info_t *of, char *rv, char *eu)
{
	char *a = NULL;
	list_t *b;
	char *c;

	if (!rv || !eu)
		return (0);

	a = malloc(_strlen(rv) + _strlen(eu) + 2);
	if (!a)
		return (1);
	_strcpy(a, rv);
	_strcat(a, "=");
	_strcat(a, eu);
	b = of->env;
	while (b)
	{
		c = starts_with(b->str, rv);
		if (c && *c == '=')
		{
			free(b->str);
			b->str = a;
			of->env_changed = 1;
			return (0);
		}
		b = b->next;
	}
	add_node_end(&(of->env), a, 0);
	free(a);
	of->env_changed = 1;
	return (0);
}
