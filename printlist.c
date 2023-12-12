#include "main.h"

/**
 * _printliststr - prints only the str of a listnode linked list
 * @head: pointer to first node in the linked list
 * Return: size of the linked llist
 *
 * Description: This function iterates through the linked list,
 * printing each string element followed by a newline character.
 * If a string is NULL, it prints "(nil)".
 */
size_t _printliststr(const listnode *head)
{
    size_t size = 0;

    while (head)
    {
        if (head->str != NULL)
            _puts(head->str);
        else
            _puts("(nil)");

        _puts("\n");
        head = head->next;
        size++;
    }
    return (size);
}
