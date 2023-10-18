#include "shell.h"

/**
 *is_chain - Test if current char in buffer is a chain delimeter
 *@nf: the parameter struct
 *@sas: the char buffer
 *@b: address of current position in buf
 *Return: 1 if chain delimeter and 0 otherwise
 */

int is_chain(info_t *nf, char *sas, size_t *b)
{
	size_t eww = *b;

	if (sas[eww] == '|' && sas[eww + 1] == '|')
	{
		sas[eww] = 0;
		eww++;
		nf->cmd_buf_type = CMD_OR;
	}
	else if (sas[eww] == '&' && sas[eww + 1] == '&')
	{
		sas[eww] = 0;
		eww++;
		nf->cmd_buf_type = CMD_AND;
	}
	else if (sas[eww] == ';') /* found end of this command */
	{
		sas[eww] = 0; /* replace semicolon with null */
		nf->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*b = eww;
	return (1);
}

/**
 *check_chain - Checks we should continue chaining based on last status
 *@zalata: the parameter struct
 *@zaka: the char buffer
 *@vv: address of current position in buf
 *@ret: starting position in buf
 *@vin: length of buf
 *Return: Void
 */

void check_chain(info_t *zalata, char *zaka, size_t *vv, size_t ret, size_t vin)
{
	size_t reta = *vv;

	if (zalata->cmd_buf_type == CMD_AND)
	{
		if (zalata->status)
		{
			zaka[ret] = 0;
			reta = vin;
		}
	}
	if (zalata->cmd_buf_type == CMD_OR)
	{
		if (!zalata->status)
		{
			zaka[ret] = 0;
			reta = vin;
		}
	}

	*vv = reta;
}

/**
 *replace_alias - Replaces an aliases in the tokenized string
 *@mago: the parameter struct
 *Return: 1 if replaced and 0 otherwise
 */

int replace_alias(info_t *mago)
{
	int zed;
	list_t *xaxo;
	char *sasa;

	for (zed = 0; zed < 10; zed++)
	{
		xaxo = node_starts_with(mago->alias, mago->argv[0], '=');
		if (!xaxo)
			return (0);
		free(mago->argv[0]);
		sasa = _strchr(xaxo->str, '=');
		if (!sasa)
			return (0);
		sasa = _strdup(sasa + 1);
		if (!sasa)
			return (0);
		mago->argv[0] = sasa;
	}
	return (1);
}

/**
 *replace_vars - Replaces vars in the tokenized string
 *@zaly: the parameter struct
 *Return: 1 if replaced and 0 otherwise
 */

int replace_vars(info_t *zaly)
{
	int lo = 0;
	list_t *ya;

	for (lo = 0; zaly->argv[lo]; lo++)
	{
		if (zaly->argv[lo][0] != '$' || !zaly->argv[lo][1])
			continue;

		if (!_strcmp(zaly->argv[lo], "$?"))
		{
			replace_string(&(zaly->argv[lo]),
					_strdup(convert_number(zaly->status, 10, 0)));
			continue;
		}
		if (!_strcmp(zaly->argv[lo], "$$"))
		{
			replace_string(&(zaly->argv[lo]),
					_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		ya = node_starts_with(zaly->env, &zaly->argv[lo][1], '=');
		if (ya)
		{
			replace_string(&(zaly->argv[lo]),
					_strdup(_strchr(ya->str, '=') + 1));
			continue;
		}
		replace_string(&zaly->argv[lo], _strdup(""));
	}
	return (0);
}

/**
 *replace_string - Replaces string
 *@han: address of old string
 *@hen: new string
 *Return: 1 if replaced 0 otherwise
 */

int replace_string(char **han, char *hen)
{
	free(*han);
	*han = hen;
	return (1);
}
