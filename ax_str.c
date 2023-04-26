#include "main.h"
/**
 * _strcat - + two str
 * @dst: pointer
 * @src: source of str
 * Return: dest - return dest
 */
char *_strcat(char *dst, const char *src)
{
	int idx, j;

	idx = 0;
	while (dst[idx] != '\0')
		idx++;

	for (j = 0; src[j] != '\0'; j++)
	{
		dst[idx] = src[j];
		idx++;
	}

	dst[idx] = '\0';
	return (dst);
}
/**
 * *_strcpy - copies the str
 * @dst: pointer
 * @src: source str
 * Return: dest - return dest
 */
char *_strcpy(char *dst, char *src)
{
	size_t idx;

	for (idx = 0; src[idx] != '\0'; idx++)
	{
		dst[idx] = src[idx];
	}
	dst[idx] = '\0';

	return (dst);
}
/**
 * _strcmp - compares two str
 * @str: type str
 * @str2: stype str
 * Return: 0
 */
int _strcmp(char *str, char *str2)
{
	int idx;

	for (idx = 0; str[idx] == str2[idx] && str[idx]; idx++)
		;

	if (str[idx] > str2[idx])
		return (1);
	if (str[idx] < str2[idx])
		return (-1);
	return (0);
}
/**
 * _strchr - locates a char
 * @str: string
 * @ch: character
 * Return: pointer - return pointer
 */
char *_strchr(char *str, char ch)
{
	unsigned int idx = 0;

	for (; *(str + idx) != '\0'; idx++)
		if (*(str + idx) == ch)
			return (str + idx);
	if (*(str + idx) == ch)
		return (str + idx);
	return ('\0');
}
/**
 * _strspn - gets the length
 * @str: initial segment
 * @acc: accepted bytes
 * Return: num of accepted bytes - return bytes
 */
int _strspn(char *str, char *acc)
{
	int idx, j, bool;

	for (idx = 0; *(str + idx) != '\0'; idx++)
	{
		bool = 1;
		for (j = 0; *(acc + j) != '\0'; j++)
		{
			if (*(str + idx) == *(acc + j))
			{
				bool = 0;
				break;
			}
		}
		if (bool == 1)
			break;
	}
	return (idx);
}
