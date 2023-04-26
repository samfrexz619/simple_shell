#include "main.h"
/**
 * cd_sh - change dir
 * @datash: data
 * Return: 1 if Success
 */
int cd_sh(data_sh *datash)
{
	char *dir;
	int izhm, izhm2, izdsh;

	dir = datash->args[1];

	if (dir != NULL)
	{
		izhm = _strcmp("$HOME", dir);
		izhm2 = _strcmp("~", dir);
		izdsh = _strcmp("--", dir);
	}
	if (dir == NULL || izhm || izhm2 || !izdsh)
	{
		cd_hm(datash);
		return (1);
	}

	if (_strcmp("-", dir) == 0)
	{
		cd_prev(datash);
		return (1);
	}
	if (_strcmp(".", dir) == 0 || _strcmp("..", dir) == 0)
	{
		_cd(datash);
		return (1);
	}
	cd_into(datash);

	return (1);
}
