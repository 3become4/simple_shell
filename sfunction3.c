#include "shell.h"



/**
 **_strchr - find character in string
 * 
 *@x: string to search
 *@c: character to look for
 *
 *Return: pointer to memory area of x
 */
char *_strchr(char *x, char c)
{
	do {
		if (*x == c)
			return (x);
	} while (*x++ != '\0');

	return (NULL);
}
/**
 * **strsplitd - splits a string into words with delimiters
 *
 * @x: the input string
 * @d: the delimeter
 *
 * Return: pointer to strings
 */
char **strsplitd(char *x, char d)
{
	int i, j, y, z, wcount = 0;
	char **s;

	if (x == NULL || x[0] == 0)
		return (NULL);
	for (i = 0; x[i] != '\0'; i++)
		if ((x[i] != d && x[i + 1] == d) ||
		    (x[i] != d && !x[i + 1]) || x[i + 1] == d)
			wcount++;
	if (wcount == 0)
		return (NULL);
	s = malloc((1 + wcount) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < wcount; j++)
	{
		while (x[i] == d && x[i] != d)
			i++;
		y = 0;
		while (x[i + y] != d && x[i + y] && x[i + y] != d)
			y++;
		s[j] = malloc((y + 1) * sizeof(char));
		if (!s[j])
		{
			for (y = 0; y < j; y++)
				free(s[y]);
			free(s);
			return (NULL);
		}
		for (z = 0; z < y; z++)
			s[j][z] = x[i++];
		s[j][z] = 0;
	}
	s[j] = NULL;
	return (s);
}

/**
 * **strsplit - splits a string into words delimiters are ignored on repeat
 *
 * @x: the input string
 * @d: the delimeter string
 *
 * Return: pointer to strings
 */

char **strsplit(char *x, char *d)
{
	int i, j, y, z, wcount = 0;
	char **s;

	if (x == NULL || x[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (i = 0; x[i] != '\0'; i++)
		if (!is_delim(x[i], d) && (is_delim(x[i + 1], d) || !x[i + 1]))
			wcount++;

	if (wcount == 0)
		return (NULL);
	s = malloc((1 + wcount) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < wcount; j++)
	{
		while (is_delim(x[i], d))
			i++;
		y = 0;
		while (!is_delim(x[i + y], d) && x[i + y])
			y++;
		s[j] = malloc((y + 1) * sizeof(char));
		if (!s[j])
		{
			for (y = 0; y < j; y++)
				free(s[y]);
			free(s);
			return (NULL);
		}
		for (z = 0; z < y; z++)
			s[j][z] = x[i++];
		s[j][z] = 0;
	}
	s[j] = NULL;
	return (s);
}