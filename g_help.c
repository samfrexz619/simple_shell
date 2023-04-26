#include "main.h"
/**
 * _help - help msg
 * @datash: data
 * Return: 0
 */
int _help(data_sh *datash)
{
	if (datash->args[1] == 0)
		xh_gen();
	else if (_strcmp(datash->args[1], "setenv") == 0)
		xh_setenv();
	else if (_strcmp(datash->args[1], "env") == 0)
		xh_env();
	else if (_strcmp(datash->args[1], "unsetenv") == 0)
		xh_unsetenv();
	else if (_strcmp(datash->args[1], "help") == 0)
		x_help();
	else if (_strcmp(datash->args[1], "exit") == 0)
		xh_exit();
	else if (_strcmp(datash->args[1], "cd") == 0)
		xh_cd();
	else if (_strcmp(datash->args[1], "alias") == 0)
		xh_aka();
	else
		write(STDERR_FILENO, datash->args[0],
		      _strlen(datash->args[0]));

	datash->status = 0;
	return (1);
}
