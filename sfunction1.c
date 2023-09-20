#include "shell.h"

/**
 * _strlen - length of a string
 *
 * @x: string
 *
 * Return: integer length of string
 */
int _strlen(char *x)
{
	int i = 0;

	if (!x)
		return (0);

	while (*x++)
		i++;
	return (i);
}
/**
 * _strcmp - lexicogarphic comparison of strings
 *
 * @x1: string
 * @x2: string
 *
 * Return: negative if x1 < x2, positive if x1 > x2, zero if x1 == x2
 */
int _strlex(char *x1, char *x2)
{
	while (*x1 && *x2)
	{
		if (*x1 != *x2)
			return (*x1 - *x2);
		x1++;
		x2++;
	}
	if (*x1 == *x2)
		return (0);
	else
		return (*x1 < *x2 ? -1 : 1);
}
/**
 * starts_with - check for start of chars
 *
 * @hay: chars to search
 * @needle: string to find
 *
 * Return: address or NULL
 */
char *starts_with(const char *hay, const char *needle)
{
	while (*needle)
		if (*needle++ != *hay++)
			return (NULL);
	return ((char *)hay);
}
/**
 * _strcat - concatenates two strings
 *
 * @x: destination 
 * @y: source
 *
 * Return: pointer to destination buffer
 */
char *_strcat(char *x, char *y)
{
	char *z = x;

	while (*x)
		x++;
	while (*y)
		*x++ = *y++;
	*x = *y;
	return (z);
}
/**
 * _strcpy - copies a string
 *
 * @x: destination
 * @y: source
 *
 * Return: pointer to destination
 */
char *_strcpy(char *x, char *y)
{
	int i = 0;

	if (x == y || y == 0)
		return (x);
	while (y[i])
	{
		x[i] = y[i];
		i++;
	}
	x[i] = 0;
	return (x);
}