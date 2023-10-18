#include "shell.h"

/**
 *get_history_file - Gets the history file
 *@eeee: parameter struct
 *Return: allocated string containg history file
 */

char *get_history_file(info_t *eeee)
{
	char *fu, *ri;

	ri = _getenv(eeee, "HOME=");
	if (!ri)
		return (NULL);
	fu = malloc(sizeof(char) * (_strlen(ri) + _strlen(HIST_FILE) + 2));
	if (!fu)
		return (NULL);
	fu[0] = 0;
	_strcpy(fu, ri);
	_strcat(fu, "/");
	_strcat(fu, HIST_FILE);
	return (fu);
}

/**
 *write_history - Creates a file, or appends to an existing file
 *@eee: the parameter struct
 *Return: 1 on success and else -1
 */

int write_history(info_t *eee)
{
	ssize_t d;
	char *da = get_history_file(eee);
	list_t *de = NULL;

	if (!da)
		return (-1);
	d = open(da, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(da);
	if (d == -1)
		return (-1);
	for (de = eee->history; de; de = de->next)
	{
		_putsfd(de->str, d);
		_putfd('\n', d);
	}
	_putfd(BUF_FLUSH, d);
	close(d);
	return (1);
}

/**
 *read_history - reads history from file
 *@fer: the parameter struct
 *Return: histcount on success, 0 otherwise
 */

int read_history(info_t *fer)
{
	int ja, je = 0, jo = 0;
	ssize_t a, b, c = 0;
	struct stat st;
	char *za = NULL, *zo = get_history_file(fer);

	if (!zo)
		return (0);
	a = open(zo, O_RDONLY);
	free(zo);
	if (a == -1)
		return (0);
	if (!fstat(a, &st))
		c = st.st_size;
	if (c < 2)
		return (0);
	za = malloc(sizeof(char) * (c + 1));
	if (!za)
		return (0);
	b = read(a, za, c);
	za[c] = 0;
	if (b <= 0)
		return (free(za), 0);
	close(a);
	for (ja = 0; ja < c; ja++)
		if (za[ja] == '\n')
		{
			za[ja] = 0;
			build_history_list(fer, za + je, jo++);
			je = ja + 1;
		}
	if (je != ja)
		build_history_list(fer, za + je, jo++);
	free(za);
	fer->histcount = jo;
	while (fer->histcount-- >= HIST_MAX)
		delete_node_at_index(&(fer->history), 0);
	renumber_history(fer);
	return (fer->histcount);
}

/**
 *build_history_list - Adds entry to a history linked list
 *@fed: Structure containing potential arguments. Used to maintain
 *@fad: buffer
 *@bru: the history linecount . histcount
 *Return: always 0
 */

int build_history_list(info_t *fed, char *fad, int bru)
{
	list_t *x = NULL;

	if (fed->history)
		x = fed->history;
	add_node_end(&x, fad, bru);
	if (!fed->history)
		fed->history = x;
	return (0);
}

/**
 *renumber_history - Renumbers the history linked list after changes
 *@io: Structure containing potential arguments. Used to maintain
 * Return: the new histcount
 */

int renumber_history(info_t *io)
{
	list_t *node = io->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (io->histcount = i);
}