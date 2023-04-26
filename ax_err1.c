#include "main.h"
/**
 * errEnv - err msg
 * @datash: data
 * Return: err msg
 */
char *errEnv(data_sh *datash)
{
	int len;
	char *err;
	char *_str;
	char *msg;

	_str = x_itoa(datash->counter);
	msg = ": Unable to add/remove from environment\n";
	len = _strlen(datash->av[0]) + _strlen(_str);
	len += _strlen(datash->args[0]) + _strlen(msg) + 4;
	err = malloc(sizeof(char) * (len + 1));
	if (err == 0)
	{
		free(err);
		free(_str);
		return (NULL);
	}

	_strcpy(err, datash->av[0]);
	_strcat(err, ": ");
	_strcat(err, _str);
	_strcat(err, ": ");
	_strcat(err, datash->args[0]);
	_strcat(err, msg);
	_strcat(err, "\0");
	free(_str);

	return (err);
}
/**
 * errPath126 - err msg for path
 * @datash: data
 * Return: err msg
 */
char *errPath126(data_sh *datash)
{
	int len;
	char *_str;
	char *err;

	_str = x_itoa(datash->counter);
	len = _strlen(datash->av[0]) + _strlen(_str);
	len += _strlen(datash->args[0]) + 24;
	err = malloc(sizeof(char) * (len + 1));
	if (err == 0)
	{
		free(err);
		free(_str);
	}
	_strcpy(err, datash->av[0]);
	_strcat(err, ": ");
	_strcat(err, _str);
	_strcat(err, ": ");
	_strcat(err, datash->args[0]);
	_strcat(err, ": Permission denied\n");
	_strcat(err, "\0");
	free(_str);
	return (err);
}
