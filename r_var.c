#include "main.h"
/**
 * check_env - checks for the type of var
 * @hd: head
 * @inp: input
 * @data: data
 * Return: nth - returns nth
 */
void check_env(r_var **hd, char *inp, data_sh *data)
{
	int row, chr, j, lval;
	char **_envr;

	_envr = data->_environ;
	for (row = 0; _envr[row]; row++)
	{
		for (j = 1, chr = 0; _envr[row][chr]; chr++)
		{
			if (_envr[row][chr] == '=')
			{
				lval = _strlen(_envr[row] + chr + 1);
				add_rvar_node(hd, j, _envr[row] + chr + 1, lval);
				return;
			}

			if (inp[j] == _envr[row][chr])
				j++;
			else
				break;
		}
	}

	for (j = 0; inp[j]; j++)
	{
		if (inp[j] == ' ' || inp[j] == '\t' || inp[j] == ';' || inp[j] == '\n')
			break;
	}

	add_rvar_node(hd, j, NULL, 0);
}
/**
 * check_vars - check typed var
 * @hd: head
 * @inp: input str
 * @st: status
 * @data: data
 * Return: nth
 */
int check_vars(r_var **hd, char *inp, char *st, data_sh *data)
{
	int idx, lst, lpd;

	lst = _strlen(st);
	lpd = _strlen(data->pid);

	for (idx = 0; inp[idx]; idx++)
	{
		if (inp[idx] == '$')
		{
			if (inp[idx + 1] == '?')
				add_rvar_node(hd, 2, st, lst), idx++;
			else if (inp[idx + 1] == '$')
				add_rvar_node(hd, 2, data->pid, lpd), idx++;
			else if (inp[idx + 1] == '\n')
				add_rvar_node(hd, 0, NULL, 0);
			else if (inp[idx + 1] == '\0')
				add_rvar_node(hd, 0, NULL, 0);
			else if (inp[idx + 1] == ' ')
				add_rvar_node(hd, 0, NULL, 0);
			else if (inp[idx + 1] == '\t')
				add_rvar_node(hd, 0, NULL, 0);
			else if (inp[idx + 1] == ';')
				add_rvar_node(hd, 0, NULL, 0);
			else
				check_env(hd, inp + idx, data);
		}
	}

	return (idx);
}
/**
 * replaced_input -replaces str
 * @head: head
 * @inp: input
 * @new_inp: new input
 * @nlen: length
 * Return: replaced str
 */
char *replaced_input(r_var **head, char *inp, char *new_inp, int nlen)
{
	r_var *idx;
	int i, j, k;

	idx = *head;
	for (j = i = 0; i < nlen; i++)
	{
		if (inp[j] == '$')
		{
			if (!(idx->len_var) && !(idx->len_val))
			{
				new_inp[i] = inp[j];
				j++;
			}
			else if (idx->len_var && !(idx->len_val))
			{
				for (k = 0; k < idx->len_var; k++)
					j++;
				i--;
			}
			else
			{
				for (k = 0; k < idx->len_val; k++)
				{
					new_inp[i] = idx->val[k];
					i++;
				}
				j += (idx->len_var);
				i--;
			}
			idx = idx->next;
		}
		else
		{
			new_inp[i] = inp[j];
			j++;
		}
	}

	return (new_inp);
}
/**
 * rep_var - replace str
 * @inp: input
 * @datash: data
 * Return: replaced str
 */
char *rep_var(char *inp, data_sh *datash)
{
	r_var *head, *idx;
	char *status, *new_input;
	int olen, nlen;

	status = aux_itoa(datash->status);
	head = NULL;

	olen = check_vars(&head, inp, status, datash);

	if (head == NULL)
	{
		free(status);
		return (inp);
	}

	idx = head;
	nlen = 0;

	while (idx != NULL)
	{
		nlen += (idx->len_val - idx->len_var);
		idx = idx->next;
	}

	nlen += olen;

	new_input = malloc(sizeof(char) * (nlen + 1));
	new_input[nlen] = '\0';

	new_input = replaced_input(&head, inp, new_input, nlen);

	free(inp);
	free(status);
	free_rvar_list(&head);

	return (new_input);
}
