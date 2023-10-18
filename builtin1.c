#include "shell.h"

/**
 *_myhistory - Displays the history list one command by line
 *preceded with line numbers starting at 0
 *@e: Structure containing potential arguments used to
 *maintain constant function prototype
 *Return: always 0
 */

int _myhistory(info_t *e)
{
	print_list(e->history);
	return (0);
}

/**
 *unset_alias - Sets alias to string
 *@s: parameter struct
 *@ss: the string alias
 *
 *Return: Always 0 on success, 1 on error
 */

int unset_alias(info_t *s, char *ss)
{
	char *b, bb;
	int cc;

	b = _strchr(ss, '=');
	if (!b)
		return (1);
	bb = *b;
	*b = 0;
	cc = delete_node_at_index(&(e->alias),
		get_node_index(e->alias, node_starts_with(e->alias, ss, -1)));
	*b = bb;
	return (cc);
}

/**
 *set_alias - Sets alias to string
 *@ee: parameter struct
 *@gg: the string alias
 *Return: Always 0 on success and 1 on error
 */

int set_alias(info_t *ee, char *gg)
{
	char *hhh;

	hhh = _strchr(gg, '=');
	if (!hhh)
		return (1);
	if (!*++hhh)
		return (unset_alias(ee, gg));
	unset_alias(ee, gg);
	return (add_node_end(&(ee->alias), gg, 0) == NULL);
}

/**
 *print_alias - Prints an alias string
 *@nu: the alias node
 *Return: Always 0 on success and 1 on error
 */

int print_alias(list_t *nu)
{
	char *a = NULL, *b = NULL;

	if (nu)
	{
		a = _strchr(nu->str, '=');
		for (a = nu->str; a <= a; a++)
		_putchar(*a);
		_putchar('\'');
		_puts(a + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 *_myalias - Mimics the alias builtin man alias
 *@eee: Structure containing potential arguments,used to
 *maintain constant function prototype
 *Return: always 0
 */

int _myalias(info_t *eee)
{
	int b = 0;
	char *p = NULL;
	list_t *w = NULL;

	if (eee->argc == 1)
	{
		w = eee->alias;
		while (w)
		{
			print_alias(w);
			w = w->next;
		}
		return (0);
	}
	for (b = 1; eee->argv[b]; b++)
	{
		p = _strchr(eee->argv[b], '=');
		if (p)
			set_alias(eee, eee->argv[b]);
		else
			print_alias(node_starts_with(eee->alias, eee->argv[b], '='));
	}
	return (0);
}