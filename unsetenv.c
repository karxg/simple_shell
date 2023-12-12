#include "main.h"

/**
 * _unsetenvwrapper - removes one or more environment variables
 * @info: pointer to the data_n struct containing shell information
 * Return: Always (0)
 *
 * Description: This function removes environment variables specified by
 * the command-line arguments in `info->argv`
 */
int _unsetenvwrapper(arginfo *info)
{
	int i;

	if (info->argc == 1)
	{
		_putserr("Too few arguements.\n");
		return (1);
	}
	i = 1;

	while (i <= info->argc)
	{
		_unsetenv(info, info->argv[i]);
		i++;
	}
	return (0);
}


/**
 * _unsetenv - removes an environment variable from the shell's environment
 * @info: pointer to the data_n struct containing shell information
 * @var: string representing the environment variable to remove
 * Return: 1 on successful deletion, 0 otherwise
 *
 * Description: This function removes the environment variable specified
 * by the string 'var'from the shell's environment
 */

int _unsetenv(arginfo *info, char *var)
{
	listnode *node = info->env;
	size_t i = 0;
	char *pre;

	if (!node || !var)
		return (0);

	while (node)
	{
		pre = _checkprefix(node->str, var);
		if (pre && *pre == '=')
		{
			info->envnew = _deletenode(&(info->env), i);
			i = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (info->envnew);
}
