#include "main.h"
/**
 * get_len - get length
 * @num: number
 * Return: length
 */
int get_len(int num)
{
	unsigned int n1;
	int len = 1;

	if (num < 0)
	{
		len++;
		n1 = num * -1;
	}
	else
	{
		n1 = num;
	}
	while (n1 > 9)
	{
		len++;
		n1 = n1 / 10;
	}

	return (len);
}
/**
 * aux_itoa - converts int
 * @num: num
 * Return: str
 */
char *aux_itoa(int num)
{
	unsigned int n1;
	int len = get_len(num);
	char *buffer;

	buffer = malloc(sizeof(char) * (len + 1));
	if (buffer == 0)
		return (NULL);

	*(buffer + len) = '\0';

	if (num < 0)
	{
		n1 = num * -1;
		buffer[0] = '-';
	}
	else
	{
		n1 = num;
	}

	len--;
	do {
		*(buffer + len) = (n1 % 10) + '0';
		n1 = n1 / 10;
		len--;
	}
	while (n1 > 0)
		;
	return (buffer);
}
/**
 * _atoi - converts str
 * @str: string
 * Return: int
 */
int _atoi(char *str)
{
	unsigned int count, size = 0, oi = 0, pn = 1, m = 1, idx;

	for (count = 0; *(str + count) != '\0'; count++)
	{
		if (size > 0 && (*(str + count) < '0' || *(str + count) > '9'))
			break;

		if (*(str + count) == '-')
			pn *= -1;

		if ((*(str + count) >= '0') && (*(str + count) <= '9'))
		{
			if (size > 0)
				m *= 10;
			size++;
		}
	}

	for (idx = count - size; idx < count; idx++)
	{
		oi = oi + ((*(str + idx) - 48) * m);
		m /= 10;
	}
	return (oi * pn);
}
