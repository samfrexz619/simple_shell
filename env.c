#include "main.h"
/**
 * cmp_env_name -compares env var
 * @nenv: name of env
 * @name: name
 * Return: 0 (or another value)
 */
int cmp_env_name(const char *nenv, const char *name)
{
	int idx;

	for (idx = 0; nenv[idx] != '='; idx++)
	{
		if (nenv[idx] != name[idx])
		{
			return (0);
		}
	}

	return (idx + 1);
}
/**
 * _getenv - get an env
 * @name: name of env
 * @_environ: env
 * Return: value of env
 */
char *_getenv(const char *name, char **_environ)
{
	char *ptr_env;
	int idx, mov;

	ptr_env = NULL;
	mov = 0;

	for (idx = 0; _environ[idx]; idx++)
	{
		mov = cmp_env_name(_environ[idx], name);
		if (mov)
		{
			ptr_env = _environ[idx];
			break;
		}
	}
	return (ptr_env + mov);
}
/**
 * _env - prints the env
 * @datash: data
 * Return: 1
 */
int _env(data_sh *datash)
{
	int idx, j;

	for (idx = 0; datash->_environ[idx]; idx++)
	{

		for (j = 0; datash->_environ[idx][j]; j++)
			;

		write(STDOUT_FILENO, datash->_environ[idx], j);
		write(STDOUT_FILENO, "\n", 1);
	}
	datash->status = 0;

	return (1);
}
