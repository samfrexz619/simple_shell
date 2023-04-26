#include "main.h"
/**
 * strcat_cd - func that concatenates
 * @datash: data
 * @msg: message
 * @err: output
 * @ver_str: counter
 * Return: err msg
 */
char *strcat_cd(data_sh *datash, char *msg, char *err, char *ver_str)
{
	char *illegal_f;

	_strcpy(err, datash->av[0]);
	_strcat(err, ": ");
	_strcat(err, ver_str);
	_strcat(err, ": ");
	_strcat(err, datash->args[0]);
	_strcat(err, msg);
	if (datash->args[1][0] == '-')
	{
		illegal_f = malloc(3);
		illegal_f[0] = '-';
		illegal_f[1] = datash->args[1][1];
		illegal_f[2] = '\0';
		_strcat(err, illegal_f);
		free(illegal_f);
	}
	else
	{
		_strcat(err, datash->args[1]);
	}

	_strcat(err, "\n");
	_strcat(err, "\0");
	return (err);
}
/**
 * err_get_cd - err msg
 * @datash: data
 * Return: err msg
 */
char *err_get_cd(data_sh *datash)
{
	int len, len_id;
	char *err, *ver_str, *msg;

	ver_str = aux_itoa(datash->counter);
	if (datash->args[1][0] == '-')
	{
		msg = ": Illegal option ";
		len_id = 2;
	}
	else
	{
		msg = ": can't cd to ";
		len_id = _strlen(datash->args[1]);
	}

	len = _strlen(datash->av[0]) + _strlen(datash->args[0]);
	len += _strlen(ver_str) + _strlen(msg) + len_id + 5;
	err = malloc(sizeof(char) * (len + 1));

	if (err == 0)
	{
		free(ver_str);
		return (NULL);
	}

	err = strcat_cd(datash, msg, err, ver_str);

	free(ver_str);

	return (err);
}
/**
 * err_not_found - err msg
 * @datash: data
 * Return: err msg
 */
char *err_not_found(data_sh *datash)
{
	int len;
	char *err;
	char *ver_str;

	ver_str = aux_itoa(datash->counter);
	len = _strlen(datash->av[0]) + _strlen(ver_str);
	len += _strlen(datash->args[0]) + 16;
	err = malloc(sizeof(char) * (len + 1));

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
	_strcat(err, ": not found\n");
	_strcat(err, "\0");
	free(ver_str);
	return (err);
}
/**
 * err_exit_shell - err msg
 * @datash: data
 * Return: err msg
 */
char *err_exit_shell(data_sh *datash)
{
	int len;
	char *err;
	char *ver_str;

	ver_str = aux_itoa(datash->counter);
	len = _strlen(datash->av[0]) + _strlen(ver_str);
	len += _strlen(datash->args[0]) + _strlen(datash->args[1]) + 23;
	err = malloc(sizeof(char) * (len + 1));
	if (err == 0)
	{
		free(ver_str);
		return (NULL);
	}
	_strcpy(err, datash->av[0]);
	_strcat(err, ": ");
	_strcat(err, ver_str);
	_strcat(err, ": ");
	_strcat(err, datash->args[0]);
	_strcat(err, ": Illegal number: ");
	_strcat(err, datash->args[1]);
	_strcat(err, "\n\0");
	free(ver_str);

	return (err);
}
