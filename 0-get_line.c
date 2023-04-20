#include "main.h"
/**
 * _line - assigns line
 * @lineptr: store the input
 * @buff: str that is called
 * @num: size of line
 * @sb: size of buff
 */
void _line(char **lineptr, size_t *num, char *buff, size_t sb)
{
	if (*lineptr == NULL)
	{
		if (sb > BSIZE)
			*num = sb;

		else
			*num = BSIZE;
		*lineptr = buff;
	}
	else if (*num < sb)
	{
		if (sb > BSIZE)
			*num = sb;
		else
			*num = BSIZE;
		*lineptr = buff;
	}
	else
	{
		_strcpy(*lineptr, buff);
		free(buff);
	}
}
/**
 * get_line - read input
 * @lineptr: buffer that stores input
 * @num: size of lineptr
 * @stream: stream
 * Return: num of bytes
 */
ssize_t get_line(char **lineptr, size_t *num, FILE *stream)
{
	int idx;
	static ssize_t inp;
	ssize_t ret;
	char *buff;
	char t = 'z';

	if (inp == 0)
		fflush(stream);
	else
		return (-1);
	inp = 0;

	buff = malloc(sizeof(char) * BSIZE);

	if (buff == 0)
		return (-1);
	while (t != '\n')
	{
		idx = read(STDIN_FILENO, &t, 1);
		if (idx == -1 || (idx == 0 && inp == 0))
		{
			free(buff);
			return (-1);
		}
		if (idx == 0 && inp != 0)
		{
			inp++;
			break;
		}
		if (inp >= BSIZE)
			buff = _realloc(buff, inp, inp + 1);
		buff[inp] = t;
		inp++;
	}
	buff[inp] = '\0';
	_line(lineptr, num, buff, inp);
	ret = inp;
	if (idx != 0)
		inp = 0;
	return (ret);
}
