#include "main.h"
/**
 * revStr - reverses a str
 * @str: string
 * Return: nth - return nth
 */
void revStr(char *str)
{
	int cnt = 0, idx, j;
	char *sr, temp;

	while (cnt >= 0)
	{
		if (str[cnt] == '\0')
			break;
		cnt++;
	}
	sr = str;

	for (idx = 0; idx < (cnt - 1); idx++)
	{
		for (j = idx + 1; j > 0; j--)
		{
			temp = *(sr + j);
			*(sr + j) = *(sr + (j - 1));
			*(sr + (j - 1)) = temp;
		}
	}
}
