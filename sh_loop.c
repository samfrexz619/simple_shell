#include "main.h"
/**
 * del_comment - deletes comments
 * @inp: input
 * Return: inp - return inp
 */
char *del_comment(char *inp)
{
	int idx, up_to;

	up_to = 0;
	for (idx = 0; inp[idx]; idx++)
	{
		if (inp[idx] == '#')
		{
			if (idx == 0)
			{
				free(inp);
				return (NULL);
			}

			if (inp[idx - 1] == ' ' || inp[idx - 1] == '\t' || inp[idx - 1] == ';')
				up_to = idx;
		}
	}
	if (up_to != 0)
	{
		inp = _realloc(inp, idx, up_to + 1);
		inp[up_to] = '\0';
	}
	return (inp);
}
/**
 * shell_lp - shell loop
 * @datash: data
 * Return: nth - returns nth
 */
void shell_lp(data_sh *datash)
{
	int lp, idx_eof;
	char *inp;

	lp = 1;
	while (lp == 1)
	{
		write(STDIN_FILENO, "($)  ", 4);
		inp = read_ln(&idx_eof);
		if (idx_eof != -1)
		{
			inp = del_comment(inp);
			if (inp == NULL)
				continue;

			if (check_err(datash, inp) == 1)
			{
				datash->status = 2;
				free(inp);
				continue;
			}
			inp = repVar(inp, datash);
			lp = split_cmd(datash, inp);
			datash->counter += 1;
			free(inp);
		}
		else
		{
			lp = 0;
			free(inp);
		}
	}
}
