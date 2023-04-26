#include "shell.h"

/**
  * _strlen - returns the lenght of the string
  * @s: the checked string
  * Return: int lenght of the string checked
  */
int _strlen(char *s)
{
	int i = 0;

	if (!s)
		return (0);

	while (*s++)
		i++;
	return (i);
}

/**
  * _strcmp - performs all lexicogarphic comparisim of two strangs
  * @s1: first strang
  * @s2: second strang
  * Return: neg if s1 is less than s2,
  *  possitve if s1 greater than s2, 0 if s1 ==s2
  */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
  * starts_with - checks if needle starts with haystack
  * @haystack: scearched string
  * @needle: found substring
  * Return: address of next char of NULL or haystack
  */

char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
  * _strcat - concatenates two strings
  * @dest: buffer destination
  * @src: buffer source
  * Return: pointer to destination buffer
  */
char *_strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}
