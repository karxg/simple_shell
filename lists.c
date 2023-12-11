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
