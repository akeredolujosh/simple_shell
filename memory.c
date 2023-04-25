#include "shell.h"


/**
 * bfree - free a pointer and NULLS an addr
 * @ptr: the addr of the pointer to be freed
 * Return: 1 if freed, else 0
 */

int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (0);
	}
	return (0);
}
