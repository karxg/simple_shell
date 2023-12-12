#include "main.h"

/**
 * _getenv - gett the value of an enverionmennt variable
 * @info: pointer to the arginfo struct containing shell information
 * @var: env var name
 * Return: the value of the environment variable or NULL if not found
 *
 * Descriptionn: This function searches for the specified environment variable
 * in the provided linked list and returns its value.
 */

char *_getenv(arginfo *info, const char *var)
{
	listnode *node = info->env;
	char *value;

	while (node)
	{
		value = _checkprefix(node->str, var);
		if (value && *value)
			return (value);
		node = node->next;
	}
	return (NULL);
}

/**
 * _envref - uppdate and retrieve the current environment variables
 * @info: pointer to the arginfo struct containing shell information
 * Return: environment variables as a string array
 *
 * Description: This function converts the linked list of environment
 * variables into a string array and returns the copy. If the
 * environment has changed, it updates the copy.
 */

char **_envref(arginfo *info)
{
	if (!info->environ || info->envnew)
	{
		info->environ = _listtoarray(info->env);
		info->envnew = 0;
	}

	return (info->environ);
}

/**
 * _printenv- prints the current environment variables
 * @info: pointer to the arginfo struct containing shell information
 * Return: (0) on success
 *
 * Description: This function prints the linked list of environment variables.
 */

int _printenv(arginfo *info)
{
	_printliststr(info->env);
	return (0);
}

/**
 * _envwrapper - set a new environment variable, or modify existing one
 * @info: pointer to the arginfo struct containing shell information
 * Return: (0) on success
 *
 * Description: This function sets or modifies an environment
 * variable with the given name to the provided value.
 */
int _envwrapper(arginfo *info)
{
	if (info->argc != 3)
	{
		_putserr("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _setenv - initialize or modify an environment variable.
 * @info: pointer to the arginfo struct containing shell information
 * @var: string representing the environment variable property
 * @val: string representing the environment variable value
 * Return: (0) on success
 *
 * Description: This function initializes a new environment
 * variable or modifies an existing one by setting the provided
 * variable name to the given value
 */

int _setenv(arginfo *info, char *var, char *val)
{
	char *buf = NULL;
	listnode *node;
	char *p;

	if (!var || !val)
		return (0);

	buf = malloc(_strlen(var) + _strlen(val) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strjoin(buf, "=");
	_strjoin(buf, val);
	node = info->env;
	while (node)
	{
		p = _checkprefix(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->envnew = 1;
			return (0);
		}
		node = node->next;
	}
	_nodetoend(&(info->env), buf, 0);
	free(buf);
	info->envnew = 1;
	return (0);
}
