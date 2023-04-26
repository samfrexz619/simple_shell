#include "main.h"
/**
 * getErr - calls the error
 * @datash: data that contains args
 * @eval: err val
 * Return: Error
 */
int getErr(data_sh *datash, int eval)
{
	char *err;

	switch (eval)
	{
	case -1:
		err = errEnv(datash);
		break;
	case 126:
		err = errPath126(datash);
		break;
	case 127:
		err = errNotf(datash);
		break;
	case 2:
		if (_strcmp("exit", datash->args[0]) == 0)
			err = errExitsh(datash);
		else if (_strcmp("cd", datash->args[0]) == 0)
			err = errCd(datash);
		break;
	}
	if (err)
	{
		write(STDERR_FILENO, err, _strlen(err));
		free(err);
	}

	datash->status = eval;
	return (eval);
}
