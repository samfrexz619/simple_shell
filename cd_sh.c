#include "main.h"
/**
 * cd_shell - change dir
 * @datash: data
 * Return: 1 if Success
 */
int cd_shell(data_sh *datash)
{
	char *dir;
	int izhom, izhome, izddash;

	dir = datash->args[1];

	if (dir != NULL)
	{
		izhom = _strcmp("$HOME", dir);
		izhome = _strcmp("~", dir);
		izddash = _strcmp("--", dir);
	}
	if (dir == NULL || izhom || izhome || !izddash)
	{
		cd_home(datash);
		return (1);
	}

	if (_strcmp("-", dir) == 0)
	{
		cd_prev(datash);
		return (1);
	}
	if (_strcmp(".", dir) == 0 || _strcmp("..", dir) == 0)
	{
		cd_dot(datash);
		return (1);
	}
	cd_to(datash);

	return (1);
}
