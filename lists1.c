#include "shell.h"

/**
 *list_len - Determines length of linked list
 *@k: pointer to first node
 *Return: size of list
 */

size_t list_len(const list_t *k)
{
	size_t m = 0;

	while (k)
	{
		k = k->next;
		m++;
	}
	return (m);
}

/**
 *list_to_strings - Returns an array of strings of the list->str
 *@fx: pointer to first node
 *Return: array of strings
 */

char **list_to_strings(list_t *fx)
{
	list_t *sakora = fx;
	size_t n = list_len(fx), b;
	char **xau;
	char *xao;

	if (!fx || !n)
		return (NULL);
	xau = malloc(sizeof(char *) * (n + 1));
	if (!xau)
		return (NULL);
	for (n = 0; sakora; sakora = sakora->next, n++)
	{
		xao = malloc(_strlen(sakora->str) + 1);
		if (!xao)
		{
			for (b = 0; b < n; b++)
				free(xau[b]);
			free(xau);
			return (NULL);
		}
		xao = _strcpy(xao, sakora->str);
		xau[n] = xao;
	}
	xau[n] = NULL;
	return (xau);
}

/**
 *print_list - Prints all elements of a list_t linked list
 *@s: pointer to first node
 *Return: size of list
 */

size_t print_list(const list_t *s)
{
	size_t e = 0;

	while (s)
	{
		_puts(convert_number(s->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(s->str ? s->str : "(nil)");
		_puts("\n");
		s = s->next;
		e++;
	}
	return (e);
}

/**
 * node_starts_with - returns node whose string starts with prefix
 * @node: pointer to list head
 * @prefix: string to match
 * @c: the next character after prefix to match
 *
 * Return: match node or null
 */
list_t *node_starts_with(list_t *a, char *b, char c)
{
	char *p = NULL;

	while (a)
	{
		p = starts_with(a->str, b);
		if (p && ((c == -1) || (*p == c)))
			return (a);
		a = a->next;
	}
	return (NULL);
}

/**
 *get_node_index - Gets the index of a node
 *@sor: pointer to list head
 *@dor: pointer to the node
 * Return: index of node or -1
 */

ssize_t get_node_index(list_t *sor, list_t *dor)
{
	size_t zar = 0;

	while (sor)
	{
		if (sor == dor)
			return (zar);
		sor = sor->next;
		zar++;
	}
	return (-1);
}
