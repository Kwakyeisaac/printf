#include "main.h"
/**
 * _printf - Printf function
 * @format : format.character strings
 * Return: Number of printed chars.
 */
int _printf(const char *format, ...)
{
	va_list args;
	int r_val;
	unsigned int h = 0;
	unsigned int r_value = 0;

	va_start(args, format);
	for ( ; format[h] != '\0' ; h++)
	{
		if (format[h] != '%')
		{
			putchar(format[h]);
		}
		else if (format[h + 1] == 'c')
		{
			putchar(va_arg(args, int));
			h++;
		}
		else if (format[h + 1] == 's')
		{
			r_val = puts(va_arg(args, char *));
			h++;
			r_value += (r_val - 1);
		}
		else if (format[h + 1] == '%')
		{
			putchar('%');
			h++;
		}
		r_value += 1;
	}
	return (r_value);
}
