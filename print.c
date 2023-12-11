#include "main.h"

/**
* _putchar - print the character c to stdout
* @c: The character to print
* Return: (1) On success, (-1) On erro
*
* Description: This function is a buffered version of the standard
* putchar function. It accumulates characters in a buffer until it is full
* or a newline character is encountered, at which point it flushes the buffer
* to stdout.
*/

int _putchar(char c)
{
	static size_t i;

	static char buf[1024];

	const char buffflush = -1;


	if (c == buffflush || i >= sizeof(buf))
	{
		write(1, buf, i);
		i = 0;
	}
	if (c != buffflush)
	{
		buf[i] = c;
		i++;
	}
	return (1);
}


/**
*_puts - prints an input string
*@str: the string to be printed
*Return: Nothing
*/
void _puts(char *str)
{
	int i = 0;

	while (str[i] != '\0')
	{
		_putchar(str[i]);
		i++;
	}
}

/**
* _putcharerr - print the character c to stderr
* @c: The character to print
* Return: Return: (1) On success, (-1) On error
*
* Description: This function is a buffered version of the standard
* fputc function. It accumulates characters in a buffer until it
* is full or a newline character is encountered, at which point it flushes
* the buffer to stderr.
*/
int _putcharerr(char c)
{
	static size_t i;

	static char buf[1024];
	const char buffflush = -1;

	if (c == buffflush || i >= sizeof(buf))
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != buffflush)
	{
		buf[i] = c;
		i++;
	}
	return (1);
}

/**
*_putserr - prints an input string
* @str: the string to be printed
* Return: Nothing
*/
void _putserr(char *str)
{
	int i = 0;

	while (str[i] != '\0')
	{
		_putcharerr(str[i]);
		i++;
	}
}

/**
* _printerr - prints an error message
* @info: pointer to the arginfo struct containing shell information
* @err: string containing specified error type
*
* Description: This function is used to print error messages to the
* standard error stream.
*/

void _printerr(arginfo *info, char *err)
{
	if (!info || !info->argv || !err)
	{
		_putserr("Error: Invalid input parameters in _printerr\n");
		return;
	}
	_putserr(": ");

	_putserr(": ");

	if (info->argv[0])
	{
		_putserr(info->argv[0]);
		_putserr(": ");
	}

	_putserr(err);
}

