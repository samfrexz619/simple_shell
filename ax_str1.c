#include "main.h"
/**
 * _strdup - duplicates a str
 * @str: string
 * Return: str - return str
 */
char *_strdup(const char *str)
{
	char *nw;
	size_t len;

	len = _strlen(str);
	nw = malloc(sizeof(char) * (len + 1));
	if (nw == NULL)
		return (NULL);
	_memcpy(nw, str, len + 1);
	return (nw);
}
/**
 * _strlen - length of a str
 * @str: pointer
 * Return: 0
 */
int _strlen(const char *str)
{
	int len;

	len = 0;
	while (str[len] != 0)
	{
		len++;
	}
	return (len);
}
/**
 * cmp_chars - compare
 * @str: string
 * @dlim: delimiter
 * Return: 1 or 0
 */
int cmp_chars(char str[], const char *dlim)
{
	unsigned int idx, j, k;

	for (idx = 0, k = 0; str[idx]; idx++)
	{
		for (j = 0; dlim[j]; j++)
		{
			if (str[idx] == dlim[j])
			{
				k++;
				break;
			}
		}
	}
	if (idx == k)
		return (1);
	return (0);
}
/**
 * _strtok - splits a str
 * @str: str
 * @dlim: delimiter
 * Return: str - return str
 */
char *_strtok(char str[], const char *dlim)
{
	static char *splittd, *str_end;
	char *str_srt;
	unsigned int idx, bool;

	if (str != NULL)
	{
		if (cmp_chars(str, dlim))
			return (NULL);
		splittd = str;
		idx = _strlen(str);
		str_end = &str[idx]; /*Stores last add*/
	}
	str_srt = splittd;
	if (str_srt == str_end) /*Reaching the end*/
		return (NULL);

	for (bool = 0; *splittd; splittd++)
	{
		/*Breaking loop finding the next token*/
		if (splittd != str_srt)
			if (*splittd && *(splittd - 1) == '\0')
				break;
		/*Replacing delimiter for null char*/
		for (idx = 0; dlim[idx]; idx++)
		{
			if (*splittd == dlim[idx])
			{
				*splittd = '\0';
				if (splittd == str_srt)
					str_srt++;
				break;
			}
		}
		if (bool == 0 && *splittd) /*Str != Dlim*/
			bool = 1;
	}
	if (bool == 0) /*Str == Delim*/
		return (NULL);
	return (str_srt);
}
/**
 * _isdigit - det str
 * @str: string
 * Return: 1 or 0
 */
int _isdigit(const char *str)
{
	unsigned int idx;

	for (idx = 0; str[idx]; idx++)
	{
		if (str[idx] < 48 || str[idx] > 57)
			return (0);
	}
	return (1);
}
