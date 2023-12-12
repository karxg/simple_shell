#include "main.h"

/**
* _getline - read a line of input and handle command chaining and EOF
* @info: Pointer to the arginfo struct containing shell information.
* Return: length of the command line or -1 on EOF
*
* Description: This function reads a line from standard input, excluding
* the newline character, and manages command chaining using
* the ';' delimiter. It updates the relevant information in the arginfo struct.
*/
ssize_t _getline(arginfo *info)
{
	const char buffflush = -1;
	static char *chain;

	static size_t i, j, bufflen;
	ssize_t result = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(buffflush);
	result = _linebuff(info, &chain, &bufflen);
	if (result == -1)
		return (-1);
	if (bufflen)
	{
		j = i;
		p = chain + i;

		while (chain[j] != ';' && j < bufflen)
			j++;

		i = j + 1;
		if (i >= bufflen)
		{
			i = bufflen = 0;
			info->ctype = 0;
		}

		*buf_p = p;
		return (_strlen(p));
	}

	*buf_p = chain;
	return (result);
}


/**
 * _linebuff - reads and buffers chained commands from stdin
 * @info: pointer to the arginfo struct containing shell information
 * @buf: address of the buffer to store the input
 * @len: address of the length variable to track the buffer size
 * Return: number of bytes read
 *
 * Description: This function reads input from the standard input and buffers
 * it for processing. It handles signals, adjusts the buffer size, and
 * updates the relevant information in the arginfo struct.
 */

ssize_t _linebuff(arginfo *info, char **buf, size_t *len)
{
	ssize_t bytesread = 0;
	size_t bufflen = 0;

	if (*len > 0)
		return (*len);

	free(*buf);
	*buf = NULL;
	signal(SIGINT, _checksigint);

	bytesread = getline(buf, &bufflen, stdin);

	if (bytesread > 0)
	{
		if ((*buf)[bytesread - 1] == '\n')
		{
			(*buf)[bytesread - 1] = '\0';
			bytesread--;
		}
		info->cmddone = 1;
		{
			*len = bytesread;
			info->cbuf = buf;
		}
	}
	return (bytesread);
}
