#include "main.h"
/**
 * cpyInfo - copies info
 * @name: name
 * @val: value
 * Return: env (or alias)
 */
char *cpyInfo(char *name, char *val)
{
	char *nw;
	int lname, lval, len;

	lname = _strlen(name);
	lval = _strlen(val);
	len = lname + lval + 2;
	nw = malloc(sizeof(char) * (len));
	_strcpy(nw, name);
	_strcat(nw, "=");
	_strcat(nw, val);
	_strcat(nw, "\0");

	return (nw);
}
/**
 * setEnv - sets an env var
 * @name: name
 * @val: value
 * @datash: data
 * Return: nth
 */
void setEnv(char *name, char *val, data_sh *datash)
{
	int b;
	char *venv, *nenv;

	for (b = 0; datash->_environ[b]; b++)
	{
		venv = _strdup(datash->_environ[b]);
		nenv = _strtok(venv, "=");
		if (_strcmp(nenv, name) == 0)
		{
			free(datash->_environ[b]);
			datash->_environ[b] = cpyInfo(nenv, val);
			free(venv);
			return;
		}
		free(venv);
	}

	datash->_environ = _reallocdp(datash->_environ, b, sizeof(char *) * (b + 2));
	datash->_environ[b] = cpyInfo(name, val);
	datash->_environ[b + 1] = NULL;
}
/**
 * _setEnv - compares env
 * @datash: data
 * Return: 1
 */
int _setEnv(data_sh *datash)
{
	if (datash->args[1] == NULL || datash->args[2] == NULL)
	{
		getErr(datash, -1);
		return (1);
	}

	setEnv(datash->args[1], datash->args[2], datash);

	return (1);
}
/**
 * _unSetEnv - deletes a env var
 * @datash: data
 * Return: 1
 */
int _unSetEnv(data_sh *datash)
{
	char **realloc_environ;
	char *venv, *nenv;
	int idx, j, k;

	if (datash->args[1] == NULL)
	{
		getErr(datash, -1);
		return (1);
	}
	k = -1;
	for (idx = 0; datash->_environ[idx]; idx++)
	{
		venv = _strdup(datash->_environ[idx]);
		nenv = _strtok(venv, "=");
		if (_strcmp(nenv, datash->args[1]) == 0)
		{
			k = idx;
		}
		free(venv);
	}
	if (k == -1)
	{
		getErr(datash, -1);
		return (1);
	}
	realloc_environ = malloc(sizeof(char *) * (idx));
	for (idx = j = 0; datash->_environ[idx]; idx++)
	{
		if (idx != k)
		{
			realloc_environ[j] = datash->_environ[idx];
			j++;
		}
	}
	realloc_environ[j] = NULL;
	free(datash->_environ[k]);
	free(datash->_environ);
	datash->_environ = realloc_environ;
	return (1);
}

