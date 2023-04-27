#include "main.h"
/**
 * strcat_cd - func that concatenates
 * @datash: data
 * @msg: message
 * @err: output
 * @_str: counter
 * Return: err msg
 */
char *strcat_cd(data_sh *datash, char *msg, char *err, char *_str)
{
	char *illegal_f;

	_strcpy(err, datash->av[0]);
	_strcat(err, ": ");
	_strcat(err, _str);
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
 * errCd - err msg
 * @datash: data
 * Return: err msg
 */
char *errCd(data_sh *datash)
{
	int len, len_id;
	char *err, *_str, *msg;

	_str = x_itoa(datash->counter);
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
	len += _strlen(_str) + _strlen(msg) + len_id + 5;
	err = malloc(sizeof(char) * (len + 1));

	if (err == 0)
	{
		free(_str);
		return (NULL);
	}

	err = strcat_cd(datash, msg, err, _str);

	free(_str);

	return (err);
}
/**
 * errNotf - err msg
 * @datash: data
 * Return: err msg
 */
char *errNotf(data_sh *datash)
{
	int len;
	char *err;
	char *_str;

	_str = x_itoa(datash->counter);
	len = _strlen(datash->av[0]) + _strlen(_str);
	len += _strlen(datash->args[0]) + 16;
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
	_strcat(err, ":not found\n");
	_strcat(err, "\0");
	free(_str);
	return (err);
}
/**
 * errExitsh - err msg
 * @datash: data
 * Return: err msg
 */
char *errExitsh(data_sh *datash)
{
	int len;
	char *err;
	char *_str;

	
	_str = x_itoa(datash->counter);
	len = _strlen(datash->av[0]) + _strlen(_str);
	len += _strlen(datash->args[0]) + _strlen(datash->args[1]) + 23;
	err = malloc(sizeof(char) * (len + 1));
	if (err == 0)
	{
		free(_str);
		return (NULL);
	}
	_strcpy(err, datash->av[0]);
	_strcat(err, ": ");
	_strcat(err, _str);
	_strcat(err, ": ");
	_strcat(err, datash->args[0]);
	_strcat(err, ": Illegal number: ");
	_strcat(err, datash->args[1]);
	_strcat(err, "\n\0");
	free(_str);

	return (err);
}
