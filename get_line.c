#include "main.h"
/**
 * assign_line - assigns line
 * @lineptr: stores input str
 * @buffer: str called
 * @nl: size of line
 * @jb: size of buff
 */
void assign_line(char **lineptr, size_t *nl, char *buffer, size_t jb)
{
	if (*lineptr == NULL)
	{
		if (jb > BSIZE)
			*nl = jb;

		else
			*nl = BSIZE;
		*lineptr = buffer;
	}
	else if (*nl < jb)
	{
		if (jb > BSIZE)
			*nl = jb;
		else
			*nl = BSIZE;
		*lineptr = buffer;
	}
	else
	{
		_strcpy(*lineptr, buffer);
		free(buffer);
	}
}
/**
 * get_line - read input from stream
 * @lineptr: stores input str
 * @nl: size of lineptr
 * @strm: stream
 * Return: num of bytes - return bytes
 */
ssize_t getLine(char **lineptr, size_t *nl, FILE *strm)
{
	int idx;
	static ssize_t inp;
	ssize_t rval;
	char *buffer;
	char t = 'z';

	if (inp == 0)
		fflush(strm);
	else
		return (-1);
	inp = 0;

	buffer = malloc(sizeof(char) * BSIZE);
	if (buffer == 0)
		return (-1);
	while (t != '\n')
	{
		idx = read(STDIN_FILENO, &t, 1);
		if (idx == -1 || (idx == 0 && inp == 0))
		{
			free(buffer);
			return (-1);
		}
		if (idx == 0 && inp != 0)
		{
			inp++;
			break;
		}
		if (inp >= BSIZE)
			buffer = _realloc(buffer, inp, inp + 1);
		buffer[inp] = t;
		inp++;
	}
	buffer[inp] = '\0';
	assign_line(lineptr, nl, buffer, inp);
	rval = inp;
	if (idx != 0)
		inp = 0;
	return (rval);
}
