#include "shell.h"

/**
 *clear_info - Initializes info_t struct
 *@fa: struct address
 */

void clear_info(info_t *fa)
{
	fa->arg = NULL;
	fa->argv = NULL;
	fa->path = NULL;
	fa->argc = 0;
}

/**
 *set_info - Initializes info_t struct
 *@in: struct address
 *@out: argument vector
 */

void set_info(info_t *in, char **out)
{
	int m = 0;

	in->fname = out[0];
	if (in->arg)
	{
		in->argv = strtow(in->arg, " \t");
		if (!in->argv)
		{
			in->argv = malloc(sizeof(char *) * 2);
			if (in->argv)
			{
				in->argv[0] = _strdup(in->arg);
				in->argv[1] = NULL;
			}
		}
		for (m = 0; in->argv && in->argv[m]; m++)
			;
		in->argc = m;

		replace_alias(in);
		replace_vars(in);
	}
}

/**
 *free_info - Frees info_t struct fields
 *@gh: struct address
 *@la: true if freeing all fields
 */

void free_info(info_t *gh, int la)
{
	ffree(gh->argv);
	gh->argv = NULL;
	gh->path = NULL;
	if (la)
	{
		if (!gh->cmd_buf)
			free(gh->arg);
		if (gh->env)
			free_list(&(gh->env));
		if (gh->history)
			free_list(&(gh->history));
		if (gh->alias)
			free_list(&(gh->alias));
		ffree(gh->environ);
			gh->environ = NULL;
		bfree((void **)gh->cmd_buf);
		if (gh->readfd > 2)
			close(gh->readfd);
		_putchar(BUF_FLUSH);
	}
}