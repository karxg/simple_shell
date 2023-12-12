#include "main.h"

#include "main.h"

/**
* _shell - execute the shell program
* @info: pointer to the arginfo struct containing shell information
* @av: array of strings representing command-line arguments
* Return: (0) on success, (1) on error
*
* Descriptionn: his function processes user input, handles
* built-in commands, and executes external commands
*/

int _shell(arginfo *info, char **av)
{
	const char buffflush = -1;
	ssize_t readresult = 0;
	int builtinresult = 0;

	while (readresult != -1 && builtinresult != -2)
	{
		_resetstruct(info);
		if (_checkmode(info))
			_puts("$ ");
		_putcharerr(buffflush);

		readresult = _getline(info);

		if (readresult != -1)
		{
			_startstruct(info, av);
			builtinresult = _isbuilt(info);

			if (builtinresult == -1)
				_getcmd(info);

		}

		else if (_checkmode(info))
			_putchar('\n');

		_freestruct(info, 0);
	}

	_freestruct(info, 1);

	return (builtinresult);
}



/**
* _shellwrapper - handling conditions and errors
* @info: pointer to the arginfo struct containing shell information
* @av: array of strings representing command-line arguments
* Return: process result
*
* Description: This function checks conditions related to interactive mode,
* potentially exiting the program. If the result is -2,
* it handles special cases involving error numbers and
* exits accordingly. The function returns the processed shell command result.
*/

int _shellwrapper(arginfo *info, char **av)
{

	int result = _shell(info, av);

	if (!_checkmode(info) && info->status)
		exit(info->status);

	if (result == -2)
	{
		if (info->errcode == -1)
			exit(info->status);

		else
		exit(info->errcode);
	}

	return (result);
}


/**
* main - entry point for the sell program
* @ac: command line arguments
* @av: array of command line argument strings
* Return: (0) on success, (1) on error
*
* Description: This function is the starting point for the shell program.
* The program initializes necessary data structures, fills the
* environment, executes the specified commands, and returns 0 on success or 1
* on error.
*/

int main(int ac __attribute__((unused)), char **av)
{
	arginfo info[] = {
	{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, 0, 0, NULL, 0, 0}
	};

	_fillenv(info);
	_shellwrapper(info, av);
	return (0);
}
