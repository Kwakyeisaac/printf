#include "main.h"
/**
 * get_width - to calculates the width for printing
 * @format: the formatted string in which to print the args.
 * @i: the list of args to be printed.
 * @list: the list of args.
 * Return: width.
 */
int get_width(const char *format, int *i, va_list list)
{
	int curr_q;
	int width = 0;

	for (curr_q = *i + 1; format[curr_q] != '\0'; curr_q++)
	{
		if (is_digit(format[curr_q]))
		{
			width *= 10;
			width += format[curr_q] - '0';
		}
		else if (format[curr_q] == '*')
		{
			curr_q++;
			width = va_arg(list, int);
			break;
		}
		else
			break;
	}
	*i = curr_q - 1;
	return (width);
}
