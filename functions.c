#include "main.h"
/************************* PRINT CHAR *************************/
/**
 * print_char - Prints a char
 * @types: List a of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: Width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_char(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	char c = va_arg(types, int);

	return (handle_write_char(c, buffer, flags, width, precision, size));
}
/************************* PRINT A STRING *************************/
/**
 * print_string - Prints a string
 * @types: List a of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_string(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	int length = 0, r;
	char *str = va_arg(types, char *);

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	if (str == NULL)
	{
		str = "(null)";
		if (precision >= 6)
			str = "      ";
	}
	while (str[length] != '\0')
		length++;
	if (precision >= 0 && precision < length)
		length = precision;
	if (width > length)
	{
		if (flags & F_MINUS)
		{
			write(1, &str[0], length);
			for (r = width - length; r > 0; r--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (r = width - length; r > 0; r--)
				write(1, " ", 1);
			write(1, &str[0], length);
			return (width);
		}
	}
return (write(1, str, length));
}
/************************* PRINT PERCENT SIGN *************************/
/**
 * print_percent - Prints a percent sign
 * @types: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_percent(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	UNUSED(types);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	return (write(1, "%%", 1));
}
/************************* PRINT INT *************************/
/**
 * print_int - Print int
 * @types: Lists of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_int(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	int r = BUFF_SIZE - 2;
	int is_negative = 0;
	long int p = va_arg(types, long int);
	unsigned long int num;

	p = convert_size_number(p, size);
	if (p == 0)
		buffer[r--] = '0';
	buffer[BUFF_SIZE - 1] = '\0';

	num = (unsigned long int)p;
	if (p < 0)
	{
		num = (unsigned long int)((-1) * p);
		is_negative = 1;
	}
	while (num > 0)
	{
		buffer[r--] = (num % 10) + '0';
		num /= 10;
	}
	r++;
	return (write_number(is_negative, r, buffer, flags, width, precision, size));
}
/************************* PRINT BINARY *************************/
/**
 * print_binary - Prints an unsigned number
 * @types: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Numbers of char printed.
 */
int print_binary(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	unsigned int p, q, r, sum;
	unsigned int s[32];
	int count;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	p = va_arg(types, unsigned int);
	q = 2147483648; /* (2 ^ 31) */
	s[0] = p / q;
	for (r = 1; r < 32; r++)
	{
		q /= 2;
		s[r] = (p / q) % 2;
	}
	for (r = 0, sum = 0, count = 0; r < 32; r++)
	{
		sum += s[r];
			if (sum || r == 31)
		{
			char z = '0' + s[r];

			write(1, &z, 1);
			count++;
		}
	}
	return (count);
}
