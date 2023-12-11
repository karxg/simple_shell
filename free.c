#include "main.h"

/**
 * _fillmem - fills memory with a constant byte
 * @dest: pointer to the memory area
 * @byte: byte to fill dest with
 * @size: number of bytes to be filled
 * Return: pointer to the memory area 'dest'
 *
 * Description: This function fills the first 'size' bytes of the memory
 * pointed to by 'dest' with the constant byte 'byte'. It returns a pointer to
 * the memory area 'dest'
 */

char *_fillmem(char *dest, char byte, unsigned int size)
{
	unsigned int i = 0;

	while (i < size)
	{
		dest[i] = byte;
		i++;
	}
	return (dest);
}

/**
 * _freepointer - free a pointer and set its address to NULL
 * @ptr: address of the pointer to free
 * Return: (1) on successfullyfreed, otherwise (0)
 *
 * Descriptoin: This function frees the memory pointed to by the given pointer
 * and sets the pointer address to NULL.
 */

int _freepointer(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}

/**
 * _freelist - free all nodes of a linked list
 * @headptr: address of the pointer to the head node
 * Return: nothing
 *
 * Description: This function frees all nodes of the linked list
 * and sets the head pointer to NULL
 */

void _freelist(listnode **headptr)
{
	listnode *node, *nextnode, *head;

	if (!headptr || !*headptr)
		return;
	head = *headptr;
	node = head;
	while (node)
	{
		nextnode = node->next;
		free(node->str);
		free(node);
		node = nextnode;
	}
	*headptr = NULL;
}

/**
 * _freearray - free a dynamic array of strings
 * @str: array of strings to free
 *
 * Description: This function frees a dynamic array of strings
 */

void _freearray(char **str)
{
	char **a = str;

	if (!str)
		return;
	while (*str)
		free(*str++);
	free(a);
}

/**
 * _freestruct - frees memory associated with arginfo struct
 * @info: pointer to the arginfo struct containing shell information
 * @field: true if freeing all fields
 *
 * Descripiton: This function frees the memory associated with
 * the arginfo struct
 */

void _freestruct(arginfo *info, int field)
{
	const char buffflush = -1;

	_freearray(info->argv);
	info->argv = NULL;
	info->path = NULL;



	if (field)
	{
		if (!info->cbuf)
			free(info->arg);

		if (info->env)
			_freelist(&(info->env));

		_freearray(info->environ);
			info->environ = NULL;

		_freepointer((void **)info->cbuf);

		if (info->rfd > 2)
			close(info->rfd);

		_putchar(buffflush);
	}
}
