#include "main.h"

/**
* _getcmd - seaarch for command int the PATH
* @info: pointer to the arginfo struct containing shell information
* Return: Nothing
*
* Description: This function searches for the specified command
* in the system's PATH, updating the information in the
* provided arginfo struct accordingly.
*/

void _getcmd(arginfo *info)
{
	char *path = NULL;

	int i = 0, k = 0;

	info->path = info->argv[0];
	if (info->cmddone == 1)
	{
		info->cmdcount++;
		info->cmddone = 0;
	}
	while (info->arg[i])
	{
		if (!_checkdelim(info->arg[i], " \t\n"))
		{
			k++;
		}
		i++;
	}
	if (!k)
	{
		return;
	}

	path = _getpath(info, _getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		_forkcmd(info);
	}
	else
	{
		if ((_checkmode(info) || _getenv(info, "PATH=")
			|| info->argv[0][0] == '/') && _checkcmd(info, info->argv[0]))
			_forkcmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			_printerr(info, "not found\n");
		}
	}
}

/**
* _getpath - search for the specified command in the given PATH string
* @info: pointer to the arginfo struct containing shell information
* @str: the PATH string to search within
* @cmd: the cmd to find int the path
* Return: full path of cmd if found or NULL
*
* Description: This function searches for the specified command in
* the provided PATH string, constructing the full path if found.
* It considers the relative path and checks each directory in the PATH.
* Returns the full path of the command if found, otherwise, returns NULL.
*/

char *_getpath(arginfo *info, char *str, char *cmd)
{
	int i = 0, p = 0;

	char *path;

	if (str == NULL)
		return (NULL);

	if ((_strlen(cmd) > 2) && _checkprefix(cmd, "./"))
	{
		if (_checkcmd(info, cmd))
			return (cmd);
	}

	while (1)
	{
		if (!str[i] || str[i] == ':')
		{
			path = _dupchars(str, p, i);
			if (!*path)
				_strjoin(path, cmd);
			else
			{
				_strjoin(path, "/");
				_strjoin(path, cmd);
			}
			if (_checkcmd(info, path))
				return (path);
			if (!str[i])
				break;
			p = i;
		}
		i++;
	}
	return (NULL);
}

/**
* _forkcmd - fork a child process and execute a command
* @info: pointer to the parameter & return info struct
* Return: nothing
*
* Description: This function forks a child process and uses execve
* to run the command specified in the arginfo struct.
* It waits for the child process to complete and updates the status
* in the arginfo struct accordingly.
*/

void _forkcmd(arginfo *info)
{
	pid_t child;

	child = fork();

	if (child == 0)
	{
		if (execve(info->path, info->argv, _envref(info)) == -1)
		{
			_freestruct(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		waitpid(child, &(info->status), 0);
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				_printerr(info, "Permission denied\n");
		}
	}
}

/**
* _dupchars - duplicate characters from the source string
* @str: source string containing the characters to be duplicated
* @start: starting index of the range
* @stop: stopping index of the range
* Return: pointer to string containing the duplicated characters
*
* Description: This function duplicates characters from the source
* string'str'within the specified range [start, stop) into a static
* buffer.Returns a pointer to a string containing the duplicated characters.
*/

char *_dupchars(char *str, int start, int stop)
{
	static char result[1024];

	int i = 0, k = 0;

	if (!str || start < 0 || stop < start)
	{
		result[0] = '\0';
		return (result);
	}

	for (i = start; i < stop; i++)
	{
		if (str[i] != ':')
		{
			result[k++] = str[i];
		}
	}

	result[k] = '\0';
	return (result);
}

