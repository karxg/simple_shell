#include "main.h"

/**
* _isbuilt- finds and execute a built-in command
* @info: pointer to the arginfo struct containing shell information
* Return: -1 if builtin not found,, 0 if builtin executed successfully,
* 1 if builtin found but not successful, -2 if builtin signals exit()
*
* Description: This function searches for the specified command
* in the built-in command table and executes it if found
*/

int _isbuilt(arginfo *info)
{
	builtin cmdtable[] = {
		{"env", _printenv},
		{"setenv", _envwrapper},
		{"unsetenv", _unsetenvwrapper},
		{"exit", _exitshell},
		{"cd", _changedir},
		{NULL, NULL}
	};

	int i = 0, result = -1;

	while (cmdtable[i].cmd != NULL)
	{
		if (_strcmp(info->argv[0], cmdtable[i].cmd) == 0)
		{
			info->cmdcount++;
			result = cmdtable[i].handler(info);
			break;
		}
		i++;
	}
	return (result);
}

/**
* _exitshell - exits the shell with a given exit status
* @info: pointer to the arginfo struct containing shell information
*  Return: exits with a status code:
* (0) if info->argv[0] is not "exit"
* (-2) if info->argv[0] is "exit" without a specified status
* sets info->errcode to the specified status or -1 for invalid input
*
* Description: This function handles the 'exit' command in the shell,
* allowing the user to exit the shell with a specified status code.
* If no status is provided, it exits with the default status of -2.
*/


int _exitshell(arginfo *info)
{
	int check;

	if (info->argv[1])
	{
		check = _atoi(info->argv[1]);

		if (check == -1)
		{
			info->status = 2;
			_printerr(info, "Illegal number: ");
			_putserr(info->argv[1]);
			return (1);
		}
		info->errcode = _atoi(info->argv[1]);
		return (-2);
	}
	info->errcode = -1;
	return (-2);
}

/**
* _cdpath - changes the currennt directory of the process
* @info: pointer to the arginfo struct containing shell information
* @path: pointer to path
* Return: (0) Success
*
* Descriptionn:This function handles the 'cd' command in the shell,
* allowing the user to change the current directory. If no directory is
* specified, it changes to the home directory. If the directory is '-', it
* changes to the previous directory. Handles updating environment variables
* (OLDPWD, PWD) accordingly. Prints error messages if the change fails.
*/

int _cdpath(arginfo *info, const char *path)
{
	char buffer[1024];

	int result;

	result = chdir(path);

	if (result == -1)
	{
		_printerr(info, "can't cd to ");
		_putserr(info->argv[1]), _putcharerr('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}

	return (result);
}

/**
* _changedir - changes the currennt directory of the process
* @info: pointer to the arginfo struct containing shell information
* Return: (0) Success
*
* Descriptionn:This function handles the 'cd' command in the shell,
* allowing the user to change the current directory. If no directory is
* specified, it changes to the home directory. If the directory is '-', it
* changes to the previous directory. Handles updating environment variables
* (OLDPWD, PWD) accordingly. Prints error messages if the change fails.
*/
int _changedir(arginfo *info)
{
	char *current, *new, buffer[1024];

	int result;

	current = getcwd(buffer, 1024);
	if (current == NULL)
	{
		_puts("Error: Unable to retrieve the current working directory.\n");
		return (-1);
	}

	if (info->argv[1] == NULL)
	{
		new = _getenv(info, "HOME=");
		result = (new == NULL) ? _cdpath(info, "/") : _cdpath(info, new);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		new = _getenv(info, "OLDPWD=");
		if (new == NULL)
		{
			_puts(current);
			_putchar('\n');
			return (1);
		}
		_puts(new), _putchar('\n');
		result = _cdpath(info, new);
	}
	else
	{
		result = _cdpath(info, info->argv[1]);
	}

	return (result);
}
