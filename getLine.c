#include "shell.h"

/**
 *input_buf - Buffers chained commands
 *@sa: parameter struct
 *@fb: address of buffer
 *@ne: address of len var
 *Return: bytes read
 */

ssize_t input_buf(info_t *sa, char **fb, size_t *ne)
{
	ssize_t q = 0;
	size_t d = 0;

	if (!*ne) /* if nothing left in the buffer, fill it */
	{
		/*bfree((void **)info->cmd_buf);*/
		free(*fb);
		*fb = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		r = getline(buf, &len_p, stdin);
#else
		q = _getline(sa, fb, &d);
#endif
		if (q > 0)
		{
			if ((*fb)[q - 1] == '\n')
			{
				(*fb)[q - 1] = '\0'; /* remove trailing newline */
				q--;
			}
			sa->linecount_flag = 1;
			remove_comments(*fb);
			build_history_list(sa, *fb, sa->histcount++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*ne = q;
				sa->cmd_buf = fb;
			}
		}
	}
	return (q);
}

/**
 *get_input - Gets a line minus the newline
 *@nf: parameter struct
 *Return: bytes read
 */

ssize_t get_input(info_t *nf)
{
	static char *ds; /* the ';' command chain buffer */
	static size_t e, g, lo;
	ssize_t z = 0;
	char **ox = &(nf->arg), *p;

	_putchar(BUF_FLUSH);
	z = input_buf(nf, &ds, &lo);
	if (z == -1) /* EOF */
		return (-1);
	if (lo) /* we have commands left in the chain buffer */
	{
		g = e; /* init new iterator to current buf position */
		p = ds + e; /* get pointer for return */

		check_chain(nf, ds, &g, e, lo);
		while (g < lo) /* iterate to semicolon or end */
		{
			if (is_chain(nf, ds, &g))
				break;
			g++;
		}
		e = g + 1; /* increment past nulled ';'' */
		if (e >= lo) /* reached end of buffer? */
		{
			e = lo = 0; /* reset position and length */
			nf->cmd_buf_type = CMD_NORM;
		}
		*ox = p; /* pass back pointer to current command position */
		return (_strlen(p)); /* return length of current command */
	}
	*ox = ds; /* else not a chain, pass back buffer from _getline() */
	return (z); /* return length of buffer from _getline() */
}

/**
 *read_buf - Reads a buffer
 *@za: parameter struct
 *@ze: buffer
 *@zo: size
 *Return: r
 */

ssize_t read_buf(info_t *za, char *ze, size_t *zo)
{
	ssize_t r = 0;

	if (*zo)
		return (0);
	r = read(za->readfd, ze, READ_BUF_SIZE);
	if (r >= 0)
		*zo = r;
	return (r);
}

/**
 *_getline - gets the next line of input from STDIN
 *@ra: parameter struct
 *@ro: address of pointer to buffer, preallocated or NULL
 *@ry: size of preallocated ptr buffer if not NULL
 *Return: s
 */

int _getline(info_t *ra, char **ro, size_t *ry)
{
	static char ew[READ_BUF_SIZE];
	static size_t x, ri;
	size_t dol;
	ssize_t r = 0, s = 0;
	char *qa = NULL, *nw = NULL, *ma;

	qa = *ro;
	if (qa && ry)
		s = *ry;
	if (x == ri)
		x = ri = 0;
	r = read_buf(ra, ew, &ri);
	if (r == -1 || (r == 0 && ri == 0))
		return (-1);
	ma = _strchr(ew + x, '\n');
	dol = ma ? 1 + (unsigned int)(ma - ew) : ri;
	nw = _realloc(qa, s, s ? s + dol : dol + 1);
	if (!nw) /* MALLOC FAILURE! */
		return (qa ? free(qa), -1 : -1);
	if (s)
		_strncat(nw, ew + x, dol - x);
	else
		_strncpy(nw, ew + x, dol - x + 1);
	s += dol - x;
	x = dol;
	qa = nw;
	if (ry)
		*ry = s;
	*ro = qa;
	return (s);
}

/**
 *sigintHandler - Blocks ctrl-C
 *@sig_num: the signal number
 *Return: void
 */

void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}