#include "main.h"

/**
 * **_strsplit - splits a string into words. ignoring repeat delimiters
 * @str: the input string to be split
 * @d: the delimeter string used for splitting
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **_strsplit(char *str, char *d)
{
	int i = 0, j, c, m, count = 0;
	char **arr;

	if (str == NULL || str[0] == '\0')
		return (NULL);
	if (d == NULL)
		d = " ";
	while (str[i] != '\0')
	{
		if (!_checkdelim(str[i], d) && (_checkdelim(str[i + 1], d) || !str[i + 1]))
			count++;
		i++;
	}
	if (count == 0)
		return (NULL);
	arr = malloc((count + 1) * sizeof(char *));
	for (i = 0, j = 0; j < count; j++)
	{
		while (_checkdelim(str[i], d))
			i++;
		c = 0;
		while (!_checkdelim(str[i + c], d) && str[i + c])
			c++;
		arr[j] = malloc((c + 1) * sizeof(char));
		for (m = 0; m < c; m++)
			arr[j][m] = str[i++];
		arr[j][m] = 0;
	}
	arr[j] = NULL;
	return (arr);
}
