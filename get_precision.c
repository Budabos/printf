#include "main.h"
/**
 *get_precision - returns the precision
 *@format: the format
 *@count: count
 *@list: list args
 *Return: int
 *
 */
int get_precision(const char *format, int *count, va_list list)
{
	int curr_count = *count + 1;
	int precision = -1;

	if (format[curr_count] != '.')
		return (precision);

	precision = 0;

	for (curr_count += 1; format[curr_count] != '\0'; curr_count++)
	{
		if (is_digit(format[curr_count]))
		{
			precision *= 10;
			precision += format[curr_count] - '0';
		}
		else if (format[curr_count] == '*')
		{
			curr_count++;
			precision = va_arg(list, int);
			break;
		}
		else
			break;
	}

	*count = curr_count - 1;

	return (precision);
}
