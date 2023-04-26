#include "main.h"
/**
 * cpy_info - copies info
 * @name: name
 * @val: value
 * Return: env (or alias)
 */
char *cpy_info(char *name, char *val)
{
	char *new;
	int len_name, len_val, len;

	len_name = _strlen(name);
	len_val = _strlen(val);
	len = len_name + len_val + 2;
	new = malloc(sizeof(char) * (len));
	_strcpy(new, name);
	_strcat(new, "=");
	_strcat(new, val);
	_strcat(new, "\0");

	return (new);
}
/**
 * set_env - sets an env var
 * @name: name
 * @val: value
 * @datash: data
 * Return: nth
 */
void set_env(char *name, char *val, data_sh *datash)
{
	int i;
	char *var_env, *name_env;

	for (i = 0; datash->_environ[i]; i++)
	{
		var_env = _strdup(datash->_environ[i]);
		name_env = _strtok(var_env, "=");
		if (_strcmp(name_env, name) == 0)
		{
			free(datash->_environ[i]);
			datash->_environ[i] = cpy_info(name_env, val);
			free(var_env);
			return;
		}
		free(var_env);
	}

	datash->_environ = _reallocdp(datash->_environ, i, sizeof(char *) * (i + 2));
	datash->_environ[i] = cpy_info(name, val);
	datash->_environ[i + 1] = NULL;
}
/**
 * _setenv - compares env
 * @datash: data
 * Return: 1
 */
int _setenv(data_sh *datash)
{
	if (datash->args[1] == NULL || datash->args[2] == NULL)
	{
		get_err(datash, -1);
		return (1);
	}

	set_env(datash->args[1], datash->args[2], datash);

	return (1);
}
/**
 * _unsetenv - deletes a env var
 * @datash: data
 * Return: 1
 */
int _unsetenv(data_sh *datash)
{
	char **realloc_environ;
	char *var_env, *name_env;
	int idx, j, k;

	if (datash->args[1] == NULL)
	{
		get_err(datash, -1);
		return (1);
	}
	k = -1;
	for (idx = 0; datash->_environ[idx]; idx++)
	{
		var_env = _strdup(datash->_environ[idx]);
		name_env = _strtok(var_env, "=");
		if (_strcmp(name_env, datash->args[1]) == 0)
		{
			k = idx;
		}
		free(var_env);
	}
	if (k == -1)
	{
		get_err(datash, -1);
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

