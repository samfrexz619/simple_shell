#include "main.h"
/**
 * getLength - get length
 * @num: number
 * Return: length - returns length
 */
int getLength(int num)
{
	unsigned int num1;
	int len = 1;

	if (num < 0)
	{
		len++;
		num1 = num * -1;
	}
	else
	{
		num1 = num;
	}
	while (num1 > 9)
	{
		len++;
		num1 = num1 / 10;
	}

	return (len);
}
/**
 * x_itoa - converts int
 * @num: num
 * Return: str - returns string
 */
char *x_itoa(int num)
{
	unsigned int num1;
	int len = getLength(num);
	char *buffer;

	buffer = malloc(sizeof(char) * (len + 1));
	if (buffer == 0)
		return (NULL);

	*(buffer + len) = '\0';

	if (num < 0)
	{
		num1 = num * -1;
		buffer[0] = '-';
	}
	else
	{
		num1 = num;
	}

	len--;
	do {
		*(buffer + len) = (num1 % 10) + '0';
		num1 = num1 / 10;
		len--;
	}
	while (num1 > 0)
		;
	return (buffer);
}
/**
 * _atoi - converts str
 * @str: string
 * Return: int - returns int
 */
int _atoi(char *str)
{
	unsigned int cnt, sz = 0, oi = 0, pn = 1, m = 1, idx;

	for (cnt = 0; *(str + cnt) != '\0'; cnt++)
	{
		if (sz > 0 && (*(str + cnt) < '0' || *(str + cnt) > '9'))
			break;

		if (*(str + cnt) == '-')
			pn *= -1;

		if ((*(str + cnt) >= '0') && (*(str + cnt) <= '9'))
		{
			if (sz > 0)
				m *= 10;
			sz++;
		}
	}

	for (idx = cnt - sz; idx < cnt; idx++)
	{
		oi = oi + ((*(str + idx) - 48) * m);
		m /= 10;
	}
	return (oi * pn);
}
