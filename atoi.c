#include "main.h"

/**
* _atoi - converts a string to an integer.
* @s: pointer to a string hoding numeric value.
* Return: an integer of converted value.
*
* Description: This function extracts and converts
* the integer value from the provided string. It takes into account
* the sign of the number and returns the corresponding integer value.
*/

int _atoi(char *s)
{
	int i = 0, result = 0, sign = 1;

	while (s[i] != '\0' && !(s[i] >= '0' && s[i] <= '9'))
	{
		if (s[i] == '-')
		{
			sign = sign * -1;
		}
		i++;
	}

	while (s[i] >= '0' && s[i] <= '9')
	{
		result = result * 10 + (sign * (s[i] - '0'));
		i++;
	}

	return (result);
}
