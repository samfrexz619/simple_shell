#include "main.h"
/**
 * err_env - err msg
 * @datash: data
 * Return: err msg
 */
char *err_env(data_sh *datash)
{
	int length;
	char *err;
	char *ver_str;
	char *msg;

	ver_str = aux_itoa(datash->counter);
	msg = ": Unable to add/remove from environment\n";
	length = _strlen(datash->av[0]) + _strlen(ver_str);
	length += _strlen(datash->args[0]) + _strlen(msg) + 4;
	err = malloc(sizeof(char) * (length + 1));
	if (err == 0)
	{
		free(err);
		free(ver_str);
		return (NULL);
	}

	_strcpy(err, datash->av[0]);
	_strcat(err, ": ");
	_strcat(err, ver_str);
	_strcat(err, ": ");
	_strcat(err, datash->args[0]);
	_strcat(err, msg);
	_strcat(err, "\0");
	free(ver_str);

	return (err);
}
/**
 * err_path_126 - err msg for path
 * @datash: data
 * Return: err str
 */
char *err_path_126(data_sh *datash)
{
	int length;
	char *ver_str;
	char *err;

	ver_str = aux_itoa(datash->counter);
	length = _strlen(datash->av[0]) + _strlen(ver_str);
	length += _strlen(datash->args[0]) + 24;
	err = malloc(sizeof(char) * (length + 1));
	if (err == 0)
	{
		free(err);
		free(ver_str);
	}
	_strcpy(err, datash->av[0]);
	_strcat(err, ": ");
	_strcat(err, ver_str);
	_strcat(err, ": ");
	_strcat(err, datash->args[0]);
	_strcat(err, ": Permission denied\n");
	_strcat(err, "\0");
	free(ver_str);
	return (err);
}
