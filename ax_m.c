#include "main.h"
/**
 * _memcpy - copies info
 * @newptr: destination
 * @ptr: source
 * @sz: size
 * Return: nth - returns nth
 */
void _memcpy(void *newptr, const void *ptr, unsigned int sz)
{
	char *ch_ptr = (char *)ptr;
	char *ch_newptr = (char *)newptr;
	unsigned int idx;

	for (idx = 0; idx < sz; idx++)
		ch_newptr[idx] = ch_ptr[idx];
}
/**
 * _realloc - reallacot memory
 * @ptr: pointer to the memory
 * @old_sz: size
 * @new_sz: new size
 * Return: ptr - returns ptr
 */
void *_realloc(void *ptr, unsigned int old_sz, unsigned int new_sz)
{
	void *newptr;

	if (ptr == NULL)
		return (malloc(new_sz));

	if (new_sz == 0)
	{
		free(ptr);
		return (NULL);
	}

	if (new_sz == old_sz)
		return (ptr);

	newptr = malloc(new_sz);
	if (newptr == NULL)
		return (NULL);

	if (new_sz < old_sz)
		_memcpy(newptr, ptr, new_sz);
	else
		_memcpy(newptr, ptr, old_sz);

	free(ptr);
	return (newptr);
}
/**
 * _reallocdp - reallocates memory
 * @ptr: double pointer
 * @old_sz: size
 * @new_sz: new size
 * Return: ptr - returns ptr
 */
char **_reallocdp(char **ptr, unsigned int old_sz, unsigned int new_sz)
{
	char **newptr;
	unsigned int idx;

	if (ptr == NULL)
		return (malloc(sizeof(char *) * new_sz));

	if (new_sz == old_sz)
		return (ptr);

	newptr = malloc(sizeof(char *) * new_sz);
	if (newptr == NULL)
		return (NULL);

	for (idx = 0; idx < old_sz; idx++)
		newptr[idx] = ptr[idx];

	free(ptr);

	return (newptr);
}
