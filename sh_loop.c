#include "main.h"
/**
 * del_comment - deletes comments
 * @inp: input
 * Return: inp
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
 * shell_loop - shell loop
 * @datash: data
 * Return: nth
 */
void shell_loop(data_sh *datash)
{
	int loop, idx_eof;
	char *inp;

	loop = 1;
	while (loop == 1)
	{
		write(STDIN_FILENO, "($)  ", 4);
		inp = read_line(&idx_eof);
		if (idx_eof != -1)
		{
			inp = del_comment(inp);
			if (inp == NULL)
				continue;

			if (check_syntax_err(datash, inp) == 1)
			{
				datash->status = 2;
				free(inp);
				continue;
			}
			inp = rep_var(inp, datash);
			loop = split_cmd(datash, inp);
			datash->counter += 1;
			free(inp);
		}
		else
		{
			loop = 0;
			free(inp);
		}
	}
}
