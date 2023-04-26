#include "main.h"
/**
 * exit_shell - exits the shell
 * @datash: data
 * Return: 0
 */
int exit_shell(data_sh *datash)
{
	unsigned int ustat;
	int is_digit;
	int str_len;
	int big_num;

	if (datash->args[1] != NULL)
	{
		ustat = _atoi(datash->args[1]);
		is_digit = _isdigit(datash->args[1]);
		str_len = _strlen(datash->args[1]);
		big_num = ustat > (unsigned int)INT_MAX;
		if (!is_digit || str_len > 10 || big_num)
		{
			get_err(datash, 2);
			datash->status = 2;
			return (1);
		}
		datash->status = (ustat % 256);
	}
	return (0);
}
