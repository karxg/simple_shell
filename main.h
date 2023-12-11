#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>

int _strlen(const char *s);
char *_strcpy(char *dest, char *src);
char *_strdup(const char *str);
char *_strjoin(char *dest, char *src);
int _strcmp(char *s1, char *s2);

/**
*struct builtin - contains a builtin string and related function
*@cmd: string representing the built-in command
*@handler: function pointer to the corresponding handler function
*/
typedef struct builtin
{
	char *cmd;
	int (*handler)(arginfo *);
} builtin;

int _isbuilt(arginfo *);
void _getcmd(arginfo *);
void _forkcmd(arginfo *);


/**
* struct listnode - singly linked list
*
* @n: the numeric field of the node
* @str: a string associated with the node
* @next: pointer to the next node in the list
*/

typedef struct listnode
{
	int n;
	char *str;
	struct listnode *next;
} listnode;

listnode *_nodetoend(listnode **, const char *, int);
size_t _printliststr(const listnode *);
int _deletenode(listnode **, unsigned int);
void _freelist(listnode **);
size_t _listlength(const listnode *);
char **_listtoarray(listnode *);

/**
 * struct arginfo - Structure containing pseudo-arguments to pass into a
 *                 function.
 *
 * @arg:           A string generated from getline containing arguments.
 * @argv:          An array of strings generated from arg.
 * @path:          A string path for the current command.
 * @argc:          The argument count.
 * @cmdcount:      The error count.
 * @errcode:       The error code for exit() calls.
 * @cmddone:       If set, count this line of input.
 * @filename:      The filename.
 * @env:           Linked list local copy of environ.
 * @environ:       Custom copy of environ from the linked list env.
 * @envnew:        If set, environ was changed.
 * @status:        The return status of the last executed command.
 * @cbuf:          Address of the pointer to command buf.
 * @ctype:         Type of command chaining.
 * @rfd:           The file descriptor from which to read line input.
 */

typedef struct arginfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int cmdcount;
	int errcode;
	int cmddone;
	char *filename;
	listnode *env;
	char **environ;
	int envnew;
	int status;
	char **cbuf;
	int ctype;
	int rfd;
} arginfo;


void _forkcmd(arginfo *info);
int _isbuilt(arginfo *info);
void _getcmd(arginfo *info);
ssize_t _linebuff(arginfo *info, char **buf, size_t *len);

int _checkcmd(arginfo *, char *);
char *_getpath(arginfo *, char *, char *);

int _checkmode(arginfo *);
void _printerr(arginfo *, char *);

int _exitshell(arginfo *);
int _changedir(arginfo *);
int _cdpath(arginfo *, const char *);

void _resetstruct(arginfo *);
void _startstruct(arginfo *, char **);
void _freestruct(arginfo *, int);

char *_getenv(arginfo *, const char *);
int _printenv(arginfo *);
int _envwrapper(arginfo *);
int _unsetenvwrapper(arginfo *);
int _fillenv(arginfo *);


#endif
