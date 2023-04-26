#include "main.h"
/**
 * swap_ch - swap | and &
 * @inp: input
 * @bool: type swap
 * Return: swapped str - returns swapped str
 */
char *swap_ch(char *inp, int bool)
{
	int idx;

	if (bool == 0)
	{
		for (idx = 0; inp[idx]; idx++)
		{
			if (inp[idx] == '|')
			{
				if (inp[idx + 1] != '|')
					inp[idx] = 16;
				else
					idx++;
			}
			if (inp[idx] == '&')
			{
				if (inp[idx + 1] != '&')
					inp[idx] = 12;
				else
					idx++;
			}
		}
	}
	else
	{
		for (idx = 0; inp[idx]; idx++)
		{
			inp[idx] = (inp[idx] == 16 ? '|' : inp[idx]);
			inp[idx] = (inp[idx] == 12 ? '&' : inp[idx]);
		}
	}
	return (inp);
}
/**
 * addNode - add separator
 * @hd_s: head
 * @hd_l: head of cmd lines list
 * @inp: input
 * Return: nth - returns nth
 */
void addNode(sep_ls **hd_s, line_ls **hd_l, char *inp)
{
	int idx;
	char *ln;

	inp = swap_ch(inp, 0);

	for (idx = 0; inp[idx]; idx++)
	{
		if (inp[idx] == ';')
			addSpNodeEnd(hd_s, inp[idx]);

		if (inp[idx] == '|' || inp[idx] == '&')
		{
			addSpNodeEnd(hd_s, inp[idx]);
			idx++;
		}
	}

	ln = _strtok(inp, ";|&");
	do {
		ln = swap_ch(ln, 1);
		addLnNodeEnd(hd_l, ln);
		ln = _strtok(NULL, ";|&");
	} while (ln != NULL);

}
/**
 * move_next - move to the next cmd
 * @list_s: sep list
 * @list_l: cmd line
 * @datash: data
 * Return: nth returns - nth
 */
void move_next(sep_ls **list_s, line_ls **list_l, data_sh *datash)
{
	int loop_sep;
	sep_ls *ls_s;
	line_ls *ls_l;

	loop_sep = 1;
	ls_s = *list_s;
	ls_l = *list_l;

	while (ls_s != NULL && loop_sep)
	{
		if (datash->status == 0)
		{
			if (ls_s->separator == '&' || ls_s->separator == ';')
				loop_sep = 0;
			if (ls_s->separator == '|')
				ls_l = ls_l->next, ls_s = ls_s->next;
		}
		else
		{
			if (ls_s->separator == '|' || ls_s->separator == ';')
				loop_sep = 0;
			if (ls_s->separator == '&')
				ls_l = ls_l->next, ls_s = ls_s->next;
		}
		if (ls_s != NULL && !loop_sep)
			ls_s = ls_s->next;
	}

	*list_s = ls_s;
	*list_l = ls_l;
}
/**
 * split_cmd - splits cmd
 * @datash: data
 * @inp: input
 * Return: 0 , 1
 */
int split_cmd(data_sh *datash, char *inp)
{
	sep_ls *head_s, *list_s;
	line_ls *head_l, *list_l;
	int loop;

	head_s = NULL;
	head_l = NULL;

	addNode(&head_s, &head_l, inp);

	list_s = head_s;
	list_l = head_l;

	while (list_l != NULL)
	{
		datash->inp = list_l->line;
		datash->args = split_ln(datash->inp);
		loop = exec_line(datash);
		free(datash->args);

		if (loop == 0)
			break;

		move_next(&list_s, &list_l, datash);

		if (list_l != NULL)
			list_l = list_l->next;
	}

		freeSpLs(&head_s);
	freeLnls(&head_l);

	if (loop == 0)
		return (0);
	return (1);
}
/**
 * split_ln - tokenizes input str
 * @inp: input
 * Return: splitted str
 */
char **split_ln(char *inp)
{
	size_t bsz;
	size_t idx;
	char **tokens;
	char *token;

	bsz = TOK_BSIZE;
	tokens = malloc(sizeof(char *) * (bsz));
	if (tokens == NULL)
	{
		write(STDERR_FILENO, ": allocation error\n", 18);
		exit(EXIT_FAILURE);
	}

	token = _strtok(inp, TOK_DLIM);
	tokens[0] = token;

	for (idx = 1; token != NULL; idx++)
	{
		if (idx == bsz)
		{
			bsz += TOK_BSIZE;
			tokens = _reallocdp(tokens, idx, sizeof(char *) * bsz);
			if (tokens == NULL)
			{
				write(STDERR_FILENO, ": allocation error\n", 18);
				exit(EXIT_FAILURE);
			}
		}
		token = _strtok(NULL, TOK_DLIM);
		tokens[idx] = token;
	}

	return (tokens);
}

