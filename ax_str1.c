#include "main.h"
/**
 * _strdup - duplicates a str
 * @str: string
 * Return: str - return str
 */
char *_strdup(const char *str)
{
	char *new;
	size_t len;

	len = _strlen(str);
	new = malloc(sizeof(char) * (len + 1));
	if (new == NULL)
		return (NULL);
	_memcpy(new, str, len + 1);
	return (new);
}
/**
 * _strlen - length of a str
 * @str: pointer
 * Return: 0
 */
int _strlen(const char *str)
{
	int len;

	for (len = 0; str[len] != 0; len++)
	{
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
	static char *splitted, *str_end;
	char *str_start;
	unsigned int idx, bool;

	if (str != NULL)
	{
		if (cmp_chars(str, dlim))
			return (NULL);
		splitted = str; /*Stores first add*/
		idx = _strlen(str);
		str_end = &str[idx]; /*Stores last add*/
	}
	str_start = splitted;
	if (str_start == str_end) /*Reaching the end*/
		return (NULL);

	for (bool = 0; *splitted; splitted++)
	{
		/*Breaking loop finding the next token*/
		if (splitted != str_start)
			if (*splitted && *(splitted - 1) == '\0')
				break;
		/*Replacing delimiter for null char*/
		for (idx = 0; dlim[idx]; idx++)
		{
			if (*splitted == dlim[idx])
			{
				*splitted = '\0';
				if (splitted == str_start)
					str_start++;
				break;
			}
		}
		if (bool == 0 && *splitted) /*Str != Dlim*/
			bool = 1;
	}
	if (bool == 0) /*Str == Delim*/
		return (NULL);
	return (str_start);
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
