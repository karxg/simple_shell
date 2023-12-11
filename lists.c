#include "main.h"

/**
* _listlength - determines the lngth of a linked list
* @head: pointer to first node
* Return: size of the linked list
*
* Description: This function determines the length of the linked list starting
* from the specified node.
*/

size_t _listlength(const listnode *head)
{
	size_t i = 0;

	while (head)
	{
		head = head->next;
		i++;
	}
	return (i);
}

/**
* _listtoarray - convert linked list to an array.
* @head: pointer to the first node of the linked list
* Return: array of strings on success, NULL on failure
*
* Description: This function takes a linked list of strings
* and converts it into a dynamically allocated array of strings.
*/

char **_listtoarray(listnode *head)
{
	listnode *node = head;
	size_t i = _listlength(head), j;
	char **strs;

	char *str;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}

/**
 * _fillenv - fill the linked list with environment variables
 * @info: pointer to the arginfo struct containing shell information
 * Return: (0) Success
 *
 * Description: This function populates a linked list with environment
 * variables and assigns it to the 'env' field of the provided 'info' structure
 */

int _fillenv(arginfo *info)
{
	listnode *node = NULL;
	size_t i = 0;

	while (environ[i])
	{
		_nodetoend(&node, environ[i], 0);
		i++;
	}

	info->env = node;
	return (0);
}

/**
 * _nodetoend - add a node to the end of a linkd list
 * @head: address of pointer to the head node
 * @str: string field of the new node
 * @n: new node index
 * Return: pointer to the newly added node, or NULL on failure
 *
 * Description: This function adds a new node with the specified string
 * and index to the end of the linked list
 */

listnode *_nodetoend(listnode **head, const char *str, int n)
{
	listnode *newnode;

	if (head == NULL)
		return (NULL);

	newnode = malloc(sizeof(listnode));

	if (newnode == NULL)
		return (NULL);

	_fillmem((void *)newnode, 0, sizeof(listnode));
	newnode->n = n;
	if (str)
	{
		newnode->str = _strdup(str);
		if (!newnode->str)
		{
			free(newnode);
			return (NULL);
		}
	}

	newnode->next = NULL;

	if (*head)
	{
		listnode *current = *head;

		while (current->next)
			current = current->next;
		current->next = newnode;
	}
	else
	{
		*head = newnode;
	}

	return (newnode);
}

/**
 * _deletenode - remove the node at specificed index
 * @head: address of the pointer to the first node
 * @n: the node to delete index
 * Return: (1) on success, (0) on failure
 *
 * Description: This function removes the node at the
 * specified index from the linked list. Returns 1 on success, 0 on failure.
 *
 */

int _deletenode(listnode **head, unsigned int n)
{
	listnode *node, *prevnode;
	unsigned int i = 0;

	if (head == NULL || *head == NULL)
		return (0);

	if (n)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	prevnode = NULL;

	while (node)
	{
		if (i == n)
		{
			if (prevnode)
				prevnode->next = node->next;
			else
				*head = node->next;

			free(node->str);
			free(node);
			return (1);
		}
		i++;
		prevnode = node;
		node = node->next;
	}
	return (0);
}
