#include "main.h"
/**
 * fr_data - frees data
 * @datash: data
 * Return: Nothing
 */
void fr_data(data_sh *datash)
{
	unsigned int idx;

	for (idx = 0; datash->_environ[idx]; idx++)
	{
		free(datash->_environ[idx]);
	}

	free(datash->_environ);
	free(datash->pid);
}

/**
 * _set - init dat
 * @datash: data
 * @av: arg vec
 * Return: nothing
 */
void _set(data_sh *datash, char **av)
{
	unsigned int idx;

	datash->av = av;
	datash->inp = NULL;
	datash->args = NULL;
	datash->status = 0;
	datash->counter = 1;

	idx = 0;

	while (environ[idx])
		idx++;

	datash->_environ = malloc(sizeof(char *) * (idx + 1));

	idx = 0;

	while (environ[idx])
	{
		datash->_environ[idx] = _strdup(environ[idx]);
		idx++;
	}

	datash->_environ[idx] = NULL;
	datash->pid = x_itoa(getpid());
}

/**
 * main - entry
 * @ac: arg count
 * @av: arg vec
 * Return: 0
 */
int main(int ac, char **av)
{
	data_sh datash;
	(void) ac;

	signal(SIGINT, get_sigint);
	_set(&datash, av);
	shell_lp(&datash);
	fr_data(&datash);
	if (datash.status < 0)
		return (255);
	return (datash.status);
}
