#include "main.h"

/**
 * _startstruct - initializes arginfo struct
 * @info: pointer to the arginfo struct
 * @av: argument vector containning command line arguments
 *
 * Description: This function initializes the arginfo struct with the provided
 * command line arguments. It sets the filename, argv, and argc fields
 * based on the given argument vector. If memory allocation fails,
 * it creates a default argv with a single argument.
 */

void _startstruct(arginfo *info, char **av)
{
	int i = 0;

	info->filename = av[0];

	if (info->arg)
	{
		info->argv = _strsplit(info->arg, " \t");

		if (!info->argv)
		{

			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
		}



	while (info->argv && info->argv[i])
	{
		i++;
	}
	info->argc = i;
	}
}

/**
 * _resetstruct - sets default values for struct arginfo
 * @info: pointer to the arginfo struct
 *
 * Description: This function sets default values for the
 * arginfo struct, including setting arg, argv, path, and argc
 * to NULL or 0 as needed.
 */

void _resetstruct(arginfo *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}
