#include "main.h"
/**
 * get_flags - Calculates active flags
 * @format: the formatted string in which to print the arguments
 * @i: to take a parameter.
 * Return: Flags:
 */
int get_flags(const char *format, int *i)
{
	/* - + 0 # ' ' */
	/* 1 2 4 8  16 */
	int r, curr_q;
	int flags = 0;
	const char FLAGS_CH[] = {'-', '+', '0', '#', ' ', '\0'};
	const int FLAGS_ARR[] = {F_MINUS, F_PLUS, F_ZERO, F_HASH, F_SPACE, 0};

	for (curr_q = *i + 1; format[curr_q] != '\0'; curr_q++)
	{
		for (r = 0; FLAGS_CH[r] != '\0'; r++)
			if (format[curr_q] == FLAGS_CH[r])
			{
				flags |= FLAGS_ARR[r];
				break;
			}
		if (FLAGS_CH[r] == 0)
			break;
	}
	*i = curr_q - 1;
	return (flags);
}
