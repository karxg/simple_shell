#include "main.h"

/**
* _strlen - calculate the length of a string
* @s: pointer to the string to calculate its length
* Return: length of string
*
* Description: This function takes a pointer to a string 's'
* and iterates through each character until it reaches the null
* terminator ('\0'). Then It returns the length of the string.
*/

int _strlen(const char *s)
{
	int i = 0;

	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

/**
 * _strcpy - copies a string
 * @dest: the destination
 * @src: the source
 * Return: pointer to destination
 */

char *_strcpy(char *dest, char *src)
{
	int i = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}

/**
* _strdup - duplicates a string
* @str: the string to duplicate
* Return: pointer to the duplicated string or NULL if @str is
* NULL or memory allocation fails.
*
* Description: Duplicates the input string @str by allocating memory for a
* new string and copying each character. Returns a pointer to
* the duplicated string.
*/

char *_strdup(const char *str)
{

	int len, i;
	char *result;

	len = 0;

	if (str == NULL)
		return (NULL);

	while (str[len] != '\0')
		len++;

	result = malloc(sizeof(char) * (len + 1));

	if (!result)
		return (NULL);

	for (i = 0; i < len; i++)
		result[i] = str[i];
	result[len] = '\0';
	return (result);
}
