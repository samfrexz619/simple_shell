#include "main.h"
/**
 * checkEnv - checks for the type of var
 * @hd: head
 * @inp: input
 * @data: data
 * Return: nth - returns nth
 */
void checkEnv(st_var **hd, char *inp, data_sh *data)
{
	int row, chr, j, lenVal;
	char **_envr;

	_envr = data->_environ;
	for (row = 0; _envr[row]; row++)
	{
		for (j = 1, chr = 0; _envr[row][chr]; chr++)
		{
			if (_envr[row][chr] == '=')
			{
				lenVal = _strlen(_envr[row] + chr + 1);
				addRvarNd(hd, j, _envr[row] + chr + 1, lenVal);
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

	addRvarNd(hd, j, NULL, 0);
}
/**
 * checkVar - check typed var
 * @hd: head
 * @inp: input str
 * @stat: status
 * @data: data
 * Return: nth
 */
int checkVar(st_var **hd, char *inp, char *stat, data_sh *data)
{
	int idx, lenst, lpd;

	lenst = _strlen(stat);
	lpd = _strlen(data->pid);

	for (idx = 0; inp[idx]; idx++)
	{
		if (inp[idx] == '$')
		{
			if (inp[idx + 1] == '?')
				addRvarNd(hd, 2, stat, lenst), idx++;
			else if (inp[idx + 1] == '$')
				addRvarNd(hd, 2, data->pid, lpd), idx++;
			else if (inp[idx + 1] == '\n')
				addRvarNd(hd, 0, NULL, 0);
			else if (inp[idx + 1] == '\0')
				addRvarNd(hd, 0, NULL, 0);
			else if (inp[idx + 1] == ' ')
				addRvarNd(hd, 0, NULL, 0);
			else if (inp[idx + 1] == '\t')
				addRvarNd(hd, 0, NULL, 0);
			else if (inp[idx + 1] == ';')
				addRvarNd(hd, 0, NULL, 0);
			else
				checkEnv(hd, inp + idx, data);
		}
	}

	return (idx);
}
/**
 * rep_inp -replaces str
 * @hd: head
 * @inp: input
 * @new_inp: new input
 * @nlen: length
 * Return: replaced str
 */
char *rep_inp(st_var **hd, char *inp, char *new_inp, int nlen)
{
	st_var *idx;
	int i, j, k;

	idx = *hd;
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
 * repVar - replace str
 * @inp: input
 * @datash: data
 * Return: replaced str
 */
char *repVar(char *inp, data_sh *datash)
{
	st_var *hd, *idx;
	char *status, *new_inp;
	int olen, nlen;

	status = x_itoa(datash->status);
	hd = NULL;

	olen = checkVar(&hd, inp, status, datash);

	if (hd == NULL)
	{
		free(status);
		return (inp);
	}

	idx = hd;
	nlen = 0;

	while (idx != NULL)
	{
		nlen += (idx->len_val - idx->len_var);
		idx = idx->next;
	}

	nlen += olen;

	new_inp = malloc(sizeof(char) * (nlen + 1));
	new_inp[nlen] = '\0';

	new_inp = rep_inp(&hd, inp, new_inp, nlen);

	free(inp);
	free(status);
	freeRvarLs(&hd);

	return (new_inp);
}
