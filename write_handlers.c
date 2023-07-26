#include "main.h"
/************************* WRITE HANDLE *************************/
/**
 * handle_write_char - it prints a string
 * @c: the character types.
 * @buffer: the buffer array to handle print
 * @flags:  it calculates active flags.
 * @width: to get width.
 * @precision: the precision specifier
 * @size: the size specifier
 *
 * Return: Number of chars printed.
 */
int handle_write_char(char c, char buffer[],
		int flags, int width, int precision, int size)
{ /* char is stored at left and paddind at buffer's right */
	int q = 0;
	char padd = ' ';

	UNUSED(precision);
	UNUSED(size);
	if (flags & F_ZERO)
		padd = '0';
	buffer[q++] = c;
	buffer[q] = '\0';
	if (width > 1)
	{
		buffer[BUFF_SIZE - 1] = '\0';
		for (q = 0; q < width - 1; q++)
			buffer[BUFF_SIZE - q - 2] = padd;
		if (flags & F_MINUS)
			return (write(1, &buffer[0], 1) +
					write(1, &buffer[BUFF_SIZE - q - 1], width - 1));
	       	else
			return (write(1, &buffer[BUFF_SIZE - q - 1], width - 1) +
					write(1, &buffer[0], 1));
	}
	return (write(1, &buffer[0], 1));
}
/************************* WRITE NUMBER *************************/
/**
 * write_number - it prints a string
 * @is_negative: List of args
 * @ind: the character types.
 * @buffer: the buffer array to handle print
 * @flags:  it calculates active flags
 * @width: to get width.
 * @precision: the precision specifier
 * @size: the size specifier
 *
 * Return: Number of chars printed.
 */
int write_number(int is_negative, int ind, char buffer[],
		int flags, int width, int precision, int size)
{
	int length = BUFF_SIZE - ind - 1;
	char padd = ' ', extra_ch = 0;

	UNUSED(size);
	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';
	if (is_negative)
		extra_ch = '-';
	else if (flags & F_PLUS)
		extra_ch = '+';
	else if (flags & F_SPACE)
		extra_ch = ' ';
	return (write_num(ind, buffer, flags, width, precision,
				length, padd, extra_ch));
}
/**
 * write_num - to write a number using a bufffer
 * @ind: an index at which the number starts on the buffer
 * @buffer: the buffer
 * @flags: the flags
 * @width: the width
 * @prec: the precision specifier
 * @length: the number length
 * @padd: the pading character
 * @extra_c: Extra character
 *
 * Return: Number of printed chars.
 */
int write_num(int ind, char buffer[],
		int flags, int width, int prec,
	int length, char padd, char extra_c)
{
	int q, padd_start = 1;

	if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0' && width == 0)
		return (0); /* printf(".0d", 0)  no char is printed */
	if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
		buffer[ind] = padd = ' '; /* width is displayed with padding ' ' */
	if (prec > 0 && prec < length)
		padd = ' ';
	while (prec > length)
		buffer[--ind] = '0', length++;
	if (extra_c != 0)
		length++;
	if (width > length)
	{
	for (q = 1; q < width - length + 1; q++)
			buffer[q] = padd;
		buffer[q] = '\0';
		if (flags & F_MINUS && padd == ' ')/* Asign extra char to left of buffer */
		{

                        if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[ind], length) + write(1, &buffer[1], q - 1));
		}
		else if (!(flags & F_MINUS) && padd == ' ')/* extra char to left of buff */
		{
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[1], q - 1) + write(1, &buffer[ind], length));
		}
		else if (!(flags & F_MINUS) && padd == '0')/* extra char to left of padd */
		{
			if (extra_c)
				buffer[--padd_start] = extra_c;
			return (write(1, &buffer[padd_start], q - padd_start) +
					write(1, &buffer[ind], length - (1 - padd_start)));
		}
	}
	if (extra_c)
			buffer[--ind] = extra_c;
	return (write(1, &buffer[ind], length));
}

/**
 * write_unsgnd - it writes an unsigned number
 * @is_negative: the number that indicates if the num is negative
 * @ind: Index at which the number starts in the buffer
 * @buffer: an array of character
 * @flags: the flags specifiers
 * @width: the width specifier
 * @precision: the precision specifier
 * @size: the size specifier
 *
 * Return: Number of written chars.
 */
int write_unsgnd(int is_negative, int ind,
		char buffer[],
	int flags, int width, int precision, int size)
{
        /* Number is stored at the Bufer's right and starts at position q */
	int length = BUFF_SIZE - ind - 1, q = 0;
	char padd = ' ';

	UNUSED(is_negative);
	UNUSED(size);
	if (precision == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
		return (0); /* printf(".0d", 0)  No character is printed */
	if (precision > 0 && precision < length)
		padd = ' ';
	while (precision > length)
	{
		buffer[--ind] = '0';
		length++;
	}
	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';
	if (width > length)
	{
		for (q = 0; q < width - length; q++)
			buffer[q] = padd;
		buffer[q] = '\0';
		if (flags & F_MINUS) /* Assign extra character to left of buffer [buffer>padd]*/
		{
			return (write(1, &buffer[ind], length) + write(1, &buffer[0], q));
		}
		else /* Assign extra character to left of padding [padd>buffer]*/
		{
			return (write(1, &buffer[0], q) + write(1, &buffer[ind], length));
		}
	}
	return (write(1, &buffer[ind], length));
}
/**
 * write_pointer - it writes a memory address
 * @buffer: an arrays of characters
 * @ind: an index at which the number starts in the buffer
 * @length: the length of number
 * @width: the width specifier
 * @flags: the flags specifier
 * @padd: the character representing the padding
 * @extra_c: the character representing extra character
 * @padd_start: an index at which padding should start
 *
 * Return: Number of written chars.
 */
int write_pointer(char buffer[], int ind, int length,
		int width, int flags, char padd, char extra_c, int padd_start)
{
	int q;

	if (width > length)
	{
		for (q = 3; q < width - length + 3; q++)
			buffer[q] = padd;
		buffer[q] = '\0';
		if (flags & F_MINUS && padd == ' ')/* Asign extra char to left of buffer */
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[ind], length) + write(1, &buffer[3], q - 3));
		}
		else if (!(flags & F_MINUS) && padd == ' ')/* extra char to left of buffer */
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[3], q - 3) + write(1, &buffer[ind], length));
		}
		else if (!(flags & F_MINUS) && padd == '0')/* extra char to left of padd */
		{
			if (extra_c)
				buffer[--padd_start] = extra_c;
			buffer[1] = '0';
			buffer[2] = 'x';
			return (write(1, &buffer[padd_start], q - padd_start) +
					write(1, &buffer[ind], length - (1 - padd_start) - 2));
		}
	}
	buffer[--ind] = 'x';
	buffer[--ind] = '0';
	if (extra_c)
		buffer[--ind] = extra_c;
	return (write(1, &buffer[ind], BUFF_SIZE - ind - 1));
}

