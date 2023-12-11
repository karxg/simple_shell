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
/**
* _checkcmd - determines if a file is an executable command
* @info: pointer to info struct containing information
* @p: path to the file to be checked
* Return: 1 if the file is an executable command, 0 otherwise.
*
* Description: This function checks whether the file specified by
* the path @p is an executable command. It uses the provided
* arginfo struct @info for context.
*/

int _checkcmd(arginfo *info, char *p)
{
	struct stat st;

	(void)info;
	if (!p || stat(p, &st) != 0)
		return (0);

	return (S_ISREG(st.st_mode));
}

/**
* _checkprefix - check if @prefix is a prefix of the @scr
* @src: string to search within
* @prefix: prefix to find
* Return: pointer to position after matched prefix in @src
* or NULL if not found.
*
* Description: Compare characters in @src and @prefix until the end of
* @prefix or a mismatch is found. Return position after the
* matched prefix in @src, or NULL if not found.
*/

char *_checkprefix(const char *src, const char *prefix)
{
	while (*prefix != '\0' && *src != '\0' && *prefix == *src)
	{
		prefix++;
		src++;
	}

	return ((*prefix == '\0') ? (char *)src : NULL);
}

/**
* _checksigint - handle the Ctrl C case
* @n:  signal number
* Return: void
*
* Description: This function is a signal handler for
* the Ctrl+C signal (SIGINT).It writes a newline and the shell prompt to
* the standard output.
*/

void _checksigint(int n)
{
	if (n == SIGINT)
	{
		write(STDOUT_FILENO, "\n$ ", 3);
	}
}
