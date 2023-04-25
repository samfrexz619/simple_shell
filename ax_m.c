#include "main.h"
/**
 * _memcpy - copies info
 * @newptr: destination
 * @ptr: source
 * @size: size
 * Return: nth
 */
void _memcpy(void *newptr, const void *ptr, unsigned int size)
{
	char *char_ptr = (char *)ptr;
	char *char_newptr = (char *)newptr;
	unsigned int idx;

	for (idx = 0; idx < size; idx++)
		char_newptr[idx] = char_ptr[idx];
}
/**
 * _realloc - reallacot memory
 * @ptr: pointer to the memory
 * @old_size: size
 * @new_size: new size
 * Return: ptr
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *newptr;

	if (ptr == NULL)
		return (malloc(new_size));

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}

	if (new_size == old_size)
		return (ptr);

	newptr = malloc(new_size);
	if (newptr == NULL)
		return (NULL);

	if (new_size < old_size)
		_memcpy(newptr, ptr, new_size);
	else
		_memcpy(newptr, ptr, old_size);

	free(ptr);
	return (newptr);
}
/**
 * _reallocdp - reallocates memory
 * @ptr: double pointer
 * @old_size: size
 * @new_size: new size
 * Return: ptr
 */
char **_reallocdp(char **ptr, unsigned int old_size, unsigned int new_size)
{
	char **newptr;
	unsigned int idx;

	if (ptr == NULL)
		return (malloc(sizeof(char *) * new_size));

	if (new_size == old_size)
		return (ptr);

	newptr = malloc(sizeof(char *) * new_size);
	if (newptr == NULL)
		return (NULL);

	for (idx = 0; idx < old_size; idx++)
		newptr[idx] = ptr[idx];

	free(ptr);

	return (newptr);
}
