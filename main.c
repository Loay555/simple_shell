#include "shell.h"

/**
 *main - Entry point
 *@a: arg count
 *@v: arg vector
 *Return: 0 on success and 1 if error
 */

int main(int a, char **v)
{
	info_t zero[] = { INFO_INIT };
	int fd = 2;

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (fd)
			: "r" (fd));

	if (a == 2)
	{
		fd = open(v[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(v[0]);
				_eputs(": 0: Can't open ");
				_eputs(v[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		zero->readfd = fd;
	}
	populate_env_list(zero);
	read_history(zero);
	hsh(zero, v);
	return (EXIT_SUCCESS);
}
