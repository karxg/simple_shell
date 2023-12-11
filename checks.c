#include "main.h"

/**
 * _checkmode - check if the shell is in interactive mode
 * @info: Pointer to the arginfo struct containing information about the shell
 * Return: 1 if in interactive mode, 0 otherwise
 *
 * Description: This function returns true (1) if the shell is running
 * in interactive mode, and false (0) otherwise. It uses the provided
 * arginfo struct @info for context.
 */

int _checkmode(arginfo *info)
{
	return (isatty(STDIN_FILENO) && info->rfd <= 2);
}

/**
 * _checkdelim - check if a character is a delimeter
 * @c: the character to check
 * @delim: the delimeter string
 * Return: 1 if true, 0 if false
 *
 * Description: This function checks if the character @c is a delimiter
 * by comparing it to the characters in the delimiter string @delim.
 * Returns 1 if true, 0 if false.
 */

int _checkdelim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

