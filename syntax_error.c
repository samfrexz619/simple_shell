#include "main.h"
/**
 * count_char - counts the repetitions of char
 * @inp: input
 * @idx: index
 * Return: Counts
 */
int count_char(char *inp, int idx)
{
	if (*(inp - 1) == *inp)
		return (count_char(inp - 1, idx + 1));

	return (idx);
}
/**
 * errSep - finds syntax errors
 * @inp: input
 * @idx: index
 * @lst: last char
 * Return: 0 when no error
 */
int errSep(char *inp, int idx, char lst)
{
	int num;

	num = 0;
	if (*inp == '\0')
		return (0);

	if (*inp == ' ' || *inp == '\t')
		return (errSep(inp + 1, idx + 1, lst));

	if (*inp == ';')
		if (lst == '|' || lst == '&' || lst == ';')
			return (idx);

	if (*inp == '|')
	{
		if (lst == ';' || lst == '&')
			return (idx);

		if (lst == '|')
		{
			num = count_char(inp, 0);
			if (num == 0 || num > 1)
				return (idx);
		}
	}

	if (*inp == '&')
	{
		if (lst == ';' || lst == '|')
			return (idx);

		if (lst == '&')
		{
			num = count_char(inp, 0);
			if (num == 0 || num > 1)
				return (idx);
		}
	}

	return (errSep(inp + 1, idx + 1, *inp));
}
/**
 * first_ch - get index of the first char
 * @inp: input
 * @idx: index
 * Return: 1 whn there's error.
 */
int first_ch(char *inp, int *idx)
{
	for (*idx = 0; inp[*idx]; *idx += 1)
	{
		if (inp[*idx] == ' ' || inp[*idx] == '\t')
			continue;

		if (inp[*idx] == ';' || inp[*idx] == '|' || inp[*idx] == '&')
			return (-1);

		break;
	}

	return (0);
}
/**
 * print_err - prints when an err is found
 * @datash: data
 * @inp: input
 * @idx: index
 * @bool: contrl msg err
 * Return: nothing
 */
void print_err(data_sh *datash, char *inp, int idx, int bool)
{
	char *msg, *msg2, *msg3, *err, *counter;
	int len;

	if (inp[idx] == ';')
	{
		if (bool == 0)
			msg = (inp[idx + 1] == ';' ? ";;" : ";");
		else
			msg = (inp[idx - 1] == ';' ? ";;" : ";");
	}
	if (inp[idx] == '|')
		msg = (inp[idx + 1] == '|' ? "||" : "|");

	if (inp[idx] == '&')
		msg = (inp[idx + 1] == '&' ? "&&" : "&");

	msg2 = ": Syntax error: \"";
	msg3 = "\" unexpected\n";
	counter = x_itoa(datash->counter);
	len = _strlen(datash->av[0]) + _strlen(counter);
	len += _strlen(msg) + _strlen(msg2) + _strlen(msg3) + 2;

	err = malloc(sizeof(char) * (len + 1));
	if (err == 0)
	{
		free(counter);
		return;
	}
	_strcpy(err, datash->av[0]);
	_strcat(err, ": ");
	_strcat(err, counter);
	_strcat(err, msg2);
	_strcat(err, msg);
	_strcat(err, msg3);
	_strcat(err, "\0");

	write(STDERR_FILENO, err, len);
	free(err);
	free(counter);
}
/**
 * check_err - print syntax err
 * @datash: data
 * @inp: input
 * Return: 1 when there's err
 */
int check_err(data_sh *datash, char *inp)
{
	int beg = 0;
	int f_ch = 0;
	int idx = 0;

	f_ch = first_ch(inp, &beg);
	if (f_ch == -1)
	{
		print_err(datash, inp, beg, 0);
		return (1);
	}

	idx = errSep(inp + beg, 0, *(inp + beg));
	if (idx != 0)
	{
		print_err(datash, inp, beg + idx, 1);
		return (1);
	}
	return (0);
}
