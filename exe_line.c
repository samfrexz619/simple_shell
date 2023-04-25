#include "main.h"
/**
 * exec_line - finds builtins
 * @datash: data
 * Return: 1
 */
int exec_line(data_sh *datash)
{
	int (*builtin)(data_sh *datash);

	if (datash->args[0] == NULL)
		return (1);

	builtin = get_builtin(datash->args[0]);

	if (builtin != NULL)
		return (builtin(datash));

	return (cmd_exec(datash));
}
