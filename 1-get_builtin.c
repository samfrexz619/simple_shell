#include "main.h"
/**
 * get_builtin - builtin that parses the cmd
 * @cmd: command
 * Return: the pointer of builtin cmd
 */
int (*get_builtin(char *cmd))(data_sh *)
{
	built_in builtins[] = {
		{ "env", prnt_env },
		{ "exit", xt_shell },
		{ "setenv", _setEnv },
		{ "unsetenv", _unSetEnv },
		{ "cd", cd_sh },
		{ "help", _help },
		{ NULL, NULL }
	};
	int idx;

	for (idx = 0; builtins[idx].name; idx++)
	{
		if (_strcmp(builtins[idx].name, cmd) == 0)
			break;
	}
	return (builtins[idx].f);
}
