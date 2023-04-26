#include "main.h"
/**
 * rev_str - reverses a str
 * @str: string
 * Return: nth - return nth
 */
void rev_str(char *str)
{
	int count = 0, idx, j;
	char *sr, temp;

	while (count >= 0)
	{
		if (str[count] == '\0')
			break;
		count++;
	}
	sr = str;

	for (idx = 0; idx < (count - 1); idx++)
	{
		for (j = idx + 1; j > 0; j--)
		{
			temp = *(sr + j);
			*(sr + j) = *(sr + (j - 1));
			*(sr + (j - 1)) = temp;
		}
	}
}
