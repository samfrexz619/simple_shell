#include "main.h"
/**
 * _cd - change dir
 * @datash: data
 * Return: Nothing
 */
void _cd(data_sh *datash)
{
	char pwd[PATH_MAX];
	char *dir, *cp_pwd, *cp_strtok_pwd;

	getcwd(pwd, sizeof(pwd));
	cp_pwd = _strdup(pwd);
	setEnv("OLDPWD", cp_pwd, datash);
	dir = datash->args[1];
	if (_strcmp(".", dir) == 0)
	{
		setEnv("PWD", cp_pwd, datash);
		free(cp_pwd);
		return;
	}
	if (_strcmp("/", cp_pwd) == 0)
	{
		free(cp_pwd);
		return;
	}
	cp_strtok_pwd = cp_pwd;
	revStr(cp_strtok_pwd);
	cp_strtok_pwd = _strtok(cp_strtok_pwd, "/");
	if (cp_strtok_pwd != NULL)
	{
		cp_strtok_pwd = _strtok(NULL, "\0");

		if (cp_strtok_pwd != NULL)
			revStr(cp_strtok_pwd);
	}
	if (cp_strtok_pwd != NULL)
	{
		chdir(cp_strtok_pwd);
		setEnv("PWD", cp_strtok_pwd, datash);
	}
	else
	{
		chdir("/");
		setEnv("PWD", "/", datash);
	}
	datash->status = 0;
	free(cp_pwd);
}
/**
 * cd_into - changes dir
 * @datash: data
 * Return: nothing
 */
void cd_into(data_sh *datash)
{
	char pwd[PATH_MAX];
	char *dir, *cp_pwd, *cp_dir;

	getcwd(pwd, sizeof(pwd));

	dir = datash->args[1];
	if (chdir(dir) == -1)
	{
		getErr(datash, 2);
		return;
	}
	cp_pwd = _strdup(pwd);
	setEnv("OLDPWD", cp_pwd, datash);
	cp_dir = _strdup(dir);
	setEnv("PWD", cp_dir, datash);

	free(cp_pwd);
	free(cp_dir);

	datash->status = 0;

	chdir(dir);
}
/**
 * cd_prev - change directory
 * @datash: data
 * Return: nth
 */
void cd_prev(data_sh *datash)
{
	char pwd[PATH_MAX];
	char *p_pwd, *p_oldpwd, *cp_pwd, *cp_oldpwd;

	getcwd(pwd, sizeof(pwd));
	cp_pwd = _strdup(pwd);

	p_oldpwd = _getEnv("OLDPWD", datash->_environ);

	if (p_oldpwd == NULL)
		cp_oldpwd = cp_pwd;
	else
		cp_oldpwd = _strdup(p_oldpwd);

	setEnv("OLDPWD", cp_pwd, datash);

	if (chdir(cp_oldpwd) == -1)
		setEnv("PWD", cp_pwd, datash);
	else
		setEnv("PWD", cp_oldpwd, datash);

	p_pwd = _getEnv("PWD", datash->_environ);

	write(STDOUT_FILENO, p_pwd, _strlen(p_pwd));
	write(STDOUT_FILENO, "\n", 1);

	free(cp_pwd);
	if (p_oldpwd)
		free(cp_oldpwd);

	datash->status = 0;

	chdir(p_pwd);
}
/**
 * cd_hm - change dir
 * @datash: data
 * Return: nth
 */
void cd_hm(data_sh *datash)
{
	char *p_pwd, *hm;
	char pwd[PATH_MAX];

	getcwd(pwd, sizeof(pwd));
	p_pwd = _strdup(pwd);

	hm = _getEnv("HOME", datash->_environ);

	if (hm == NULL)
	{
		setEnv("OLDPWD", p_pwd, datash);
		free(p_pwd);
		return;
	}
	if (chdir(hm) == -1)
	{
		getErr(datash, 2);
		free(p_pwd);
		return;
	}

	setEnv("OLDPWD", p_pwd, datash);
	setEnv("PWD", hm, datash);
	free(p_pwd);
	datash->status = 0;
}
