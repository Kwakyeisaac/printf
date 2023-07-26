#include "main.h"
/**
 * get_precision - to calculates the precision for printing
 * @format: formatted string in which to print the args
 * @i: to list args to be printed.
 * @list: list of args.
 * Return: Precision.
 */
int get_precision(const char *format, int *i, va_list list)
{
	int curr_q = *i + 1;
	int precision = -1;

	if (format[curr_q] != '.')
		return (precision);
	precision = 0;
	for (curr_q += 1; format[curr_q] != '\0'; curr_q++)
	{
		if (is_digit(format[curr_q]))
		{
			precision *= 10;
			precision += format[curr_q] - '0';
		}
		else if (format[curr_q] == '*')
		{
			curr_q++;
			precision = va_arg(list, int);
			break;
		}
		else
			break;
	}
	*i = curr_q - 1;
	return (precision);
}
