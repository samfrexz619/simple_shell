#include "main.h"
/**
 * read_line - reads the input
 * @idx_eof: val of getline
 * Return: input str - (input string)
 */
char *read_line(int *idx_eof)
{
	char *inp = NULL;
	size_t bufsize = 0;

	*idx_eof = getline(&inp, &bufsize, stdin);

	return (inp);
}
