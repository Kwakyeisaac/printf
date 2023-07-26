#include "main.h"
#include <stdarg.h>
/****************** PRINT POINTER ******************/
/**
 * print_pointer - Prints the value of a pointer variable
 * @types: to list a of arguments
 * @buffer: to buffer array to handle print
 * @flags: to calculates the active flags
 * @width: to get width
 * @precision: the precision specification
 * @size: the size specifier
 * Return: the number of characters printed.
 */
int print_pointer(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	char extra_c = 0, padd = ' ';
	int ind = BUFF_SIZE - 2, length = 2, padd_start = 1; /* length=2, for '0x' */
	unsigned long num_addrs;
	char map_to[] = "0123456789abcdef";
	void *addrs = va_arg(types, void*);

	UNUSED(width);
	UNUSED(size);
	if (addrs == NULL)
		return (write(1, "(nil)", 5));
	buffer[BUFF_SIZE - 1] = '\0';
	UNUSED(precision);
	num_addrs = (unsigned long)addrs;
	while (num_addrs > 0)
	{
		buffer[ind--] = map_to[num_addrs % 16];
		num_addrs /= 16;
		length++;
	}
	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';
	if (flags & F_PLUS)
		extra_c = '+', length++;
	else if (flags & F_SPACE)
		extra_c = ' ', length++;
	ind++;
	/*return (write(1, &buffer[i], BUFF_SIZE - i - 1));*/
	return (write_pointer(buffer, ind, length,
				width, flags, padd, extra_c, padd_start));
}
/************************* PRINT NON PRINTABLE *************************/
/**
 * print_non_printable - to prints ascii codes in hexa of non printable chars
 * @types: lista of args
 * @buffer: to buffer the array to handle print
 * @flags: to calculates the active flags
 * @width: to get width
 * @precision: the precision specification
 * @size: the size specifier
 * Return: the number of characters printed
 */
int print_non_printable(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	int q = 0, offset = 0;
	char *str = va_arg(types, char *);

	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	if (str == NULL)
		return (write(1, "(null)", 6));
	while (str[q] != '\0')
	{
		if (is_printable(str[q]))
			buffer[q + offset] = str[q];
		else
			offset += append_hexa_code(str[q], buffer, q + offset);
		q++;
	}
	buffer[q + offset] = '\0';
	return (write(1, buffer, q + offset));
}
/************************* PRINT REVERSE *************************/
/**
 * print_reverse - Prints reverse string.
 * @types: to lista of arg
 * @buffer: to buffer the array to handle print
 * @flags: to calculates the active flags
 * @width: to get width
 * @precision: the precision specification
 * @size: the size specifier
 * Return: the numbers of characters printed
 */
int print_reverse(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	char *str;
	int q, count = 0;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(size);
	str = va_arg(types, char *);
	if (str == NULL)
	{
		UNUSED(precision);
		str = ")Null(";
	}
	for (q = 0; str[q]; q++)
		;
	for (q = q - 1; q >= 0; q--)
	{
		char v = str[q];

		write(1, &v, 1);
		count++;
	}
	return (count);
}
/************************* PRINT A STRING IN ROT13 *************************/
/**
 * print_rot13string - to print a string in rot13.
 * @types: to list of arg
 * @buffer: to buffer an array to handle print
 * @flags: to calculates active flags
 * @width: to get width
 * @precision: precision specification
 * @size: Size specifier
 * Return: the numbers of chars printed
 */
int print_rot13string(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	char p;
	char *str;
	unsigned int q, r;
	int count = 0;
	char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	str = va_arg(types, char *);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	if (str == NULL)
		str = "(AHYY)";
	for (q = 0; str[q]; q++)
	{
		for (r = 0; in[r]; r++)
		{
			if (in[r] == str[q])
			{
				p = out[r];
				write(1, &p, 1);
				count++;
				break;
			}
		}
		if (!in[r])
		{
			p = str[q];
			write(1, &p, 1);
			count++;
		}
	}
	return (count);
}
