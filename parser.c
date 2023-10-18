#include "shell.h"

/**
 *is_cmd - Determines if a file is an executable command
 *@nf: the info struct
 *@zak: path to the file
 *Return: 1 if true, 0 otherwise
 */

int is_cmd(info_t *nf, char *zak)
{
	struct stat st;

	(void)nf;
	if (!zak || stat(zak, &st))
		return (0);
	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 *dup_chars - Duplicates characters
 *@tr: the PATH string
 *@ar: starting index
 *@ap: stopping index
 *Return: pointer to new buffer
 */

char *dup_chars(char *tr, int ar, int ap)
{
	static char buf[1024];
	int e = 0, v = 0;

	for (v = 0, e = ar; e < ap; e++)
		if (tr[e] != ':')
			buf[v++] = tr[e];
	buf[v] = 0;
	return (buf);
}

/**
 *find_path - Finds this cmd in the PATH string
 *@nf: the info struct
 *@th: the PATH string
 *@dm: the cmd to find
 *Return: full path of cmd if found or NULL
 */

char *find_path(info_t *nf, char *th, char *dm)
{
	int g = 0, zal = 0;
	char *path;

	if (!th)
		return (NULL);
	if ((_strlen(dm) > 2) && starts_with(dm, "./"))
	{
		if (is_cmd(nf, dm))
			return (dm);
	}
	while (1)
	{
		if (!th[g] || th[g] == ':')
		{
			path = dup_chars(th, zal, g);
			if (!*path)
				_strcat(path, dm);
			else
			{
				_strcat(path, "/");
				_strcat(path, dm);
			}
			if (is_cmd(nf, path))
				return (path);
			if (!th[g])
				break;
			zal = g;
		}
		g++;
	}
	return (NULL);
}