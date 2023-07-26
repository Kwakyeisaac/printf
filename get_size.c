#include "main.h"
/**
 * get_size - to calculates the size to cast the args
 * @format: the formatted string in which to print the args
 * @i: the list of args to be printed.
 * Return: Precision.
 */
int get_size(const char *format, int *i)
{
	int curr_q = *i + 1;
	int size = 0;

	if (format[curr_q] == 'l')
		size = S_LONG;
	else if (format[curr_q] == 'h')
		size = S_SHORT;
	if (size == 0)
		*i = curr_q - 1;
	else
		*i = curr_q;
	return (size);
}
