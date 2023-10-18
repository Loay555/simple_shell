#include "shell.h"

/**
 *hsh - Main shell loop
 *@nii: the parameter & return info struct
 *@var: the argument vector from main()
 * Return: 0 on success, 1 on error, or error code
 */

int hsh(info_t *nii, char **var)
{
	ssize_t f = 0;
	int dara = 0;

	while (f != -1 && dara != -2)
	{
		clear_info(nii);
		if (interactive(nii))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		f = get_input(nii);
		if (f != -1)
		{
			set_info(nii, var);
			dara = find_builtin(nii);
			if (dara == -1)
				find_cmd(nii);
		}
		else if (interactive(nii))
			_putchar('\n');
		free_info(nii, 0);
	}
	write_history(nii);
	free_info(nii, 1);
	if (!interactive(nii) && nii->status)
		exit(nii->status);
	if (dara == -2)
	{
		if (nii->err_num == -1)
			exit(nii->status);
		exit(nii->err_num);
	}
	return (dara);
}

/**
 *find_builtin - finds a builtin command
 *@zalo: the parameter and return info struct
 *Return: -1 if builtin not found
 *0 if builtin executed successfully
 *1 if builtin found but not successful
 *2 if builtin signals exit()
 */

int find_builtin(info_t *zalo)
{
	int rag, bo = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (rag = 0; builtintbl[rag].type; rag++)
		if (_strcmp(zalo->argv[0], builtintbl[rag].type) == 0)
		{
			zalo->line_count++;
			bo = builtintbl[rag].func(zalo);
			break;
		}
	return (bo);
}

/**
 *find_cmd - Finds a command in PATH
 *@dako: the parameter & return info struct
 *Return: void
 */

void find_cmd(info_t *dako)
{
	char *cara = NULL;
	int e, p;

	dako->path = dako->argv[0];
	if (dako->linecount_flag == 1)
	{
		dako->line_count++;
		dako->linecount_flag = 0;
	}
	for (e = 0, p = 0; dako->arg[e]; e++)
		if (!is_delim(dako->arg[e], " \t\n"))
			p++;
	if (!p)
		return;
	cara = find_path(dako, _getenv(dako, "PATH="), dako->argv[0]);
	if (cara)
	{
		dako->path = cara;
		fork_cmd(dako);
	}
	else
	{
		if ((interactive(dako) || _getenv(dako, "PATH=")
					|| dako->argv[0][0] == '/') && is_cmd(dako, dako->argv[0]))
			fork_cmd(dako);
		else if (*(dako->arg) != '\n')
		{
			dako->status = 127;
			print_error(dako, "not found\n");
		}
	}
}

/**
 *fork_cmd - forks a an exec thread to run cmd
 *@mad: the parameter and return info struct
 *Return: void
 */

void fork_cmd(info_t *mad)
{
	pid_t xax;

	xax = fork();
	if (xax == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (xax == 0)
	{
		if (execve(mad->path, mad->argv, get_environ(mad)) == -1)
		{
			free_info(mad, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(mad->status));
		if (WIFEXITED(mad->status))
		{
			mad->status = WEXITSTATUS(mad->status);
			if (mad->status == 126)
				print_error(mad, "Permission denied\n");
		}
	}
}