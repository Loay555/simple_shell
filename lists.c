#include "shell.h"

/**
 *add_node - adds a node to the start of the list
 *@ad: address of pointer to head node
 *@add: str field of node
 *@addd: node index used by history
 *Return: size of list
 */

list_t *add_node(list_t **ad, const char *add, int addd)
{
	list_t *new_head;

	if (!ad)
		return (NULL);
	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL);
	_memset((void *)new_head, 0, sizeof(list_t));
	new_head->num = addd;
	if (add)
	{
		new_head->str = _strdup(add);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *ad;
	*ad = new_head;
	return (new_head);
}

/**
 *add_node_end - Adds a node to the end of the list
 *@sa: address of pointer to head node
 *@se: str field of node
 *@so: node index used by history
 *Return: size of list
 */

list_t *add_node_end(list_t **sa, const char *se, int so)
{
	list_t *x, *y;

	if (!sa)
		return (NULL);
	y = *sa;
	x = malloc(sizeof(list_t));
	if (!x)
		return (NULL);
	_memset((void *)x, 0, sizeof(list_t));
	x->num = so;
	if (se)
	{
		x->str = _strdup(se);
		if (!x->str)
		{
			free(x);
			return (NULL);
		}
	}
	if (y)
	{
		while (y->next)
			y = y->next;
		y->next = x;
	}
	else
		*sa = x;
	return (x);
}

/**
 *print_list_str - Prints only the str element of a list_t linked list
 *@e: pointer to first node
 *Return: size of list
 */

size_t print_list_str(const list_t *e)
{
	size_t d = 0;

	while (e)
	{
		_puts(e->str ? e->str : "(nil)");
		_puts("\n");
		e = e->next;
		d++;
	}
	return (d);
}

/**
 *delete_node_at_index - deletes node at given index
 *@hd: address of pointer to first node
 *@xd: index of node to delete
 *Return: 1 on success 0 if fail
 */

int delete_node_at_index(list_t **hd, unsigned int xd)
{
	list_t *f, *z;
	unsigned int v = 0;

	if (!hd || !*hd)
		return (0);
	if (!xd)
	{
		f = *hd;
		*hd = (*hd)->next;
		free(f->str);
		free(f);
		return (1);
	}
	f = *hd;
	while (f)
	{
		if (v == xd)
		{
			z->next = f->next;
			free(f->str);
			free(f);
			return (1);
		}
		v++;
		z = f;
		f = f->next;
	}
	return (0);
}

/**
 *free_list - Frees all nodes of a list
 *@rp: address of pointer to head node
 *Return: void
 */

void free_list(list_t **rp)
{
	list_t *x, *y, *z;

	if (!rp || !*rp)
		return;
	z = *rp;
	x = z;
	while (x)
	{
		y = x->next;
		free(x->str);
		free(x);
		x = y;
	}
	*rp = NULL;
}