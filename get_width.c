#include "main.h"

/**
 * get_width - Calculates width
 * @format: Format
 * @count: List of aeg
 * @list: list of arg
 * Return: width.
 */
int get_width(const char *format, int *count, va_list list)
{
	int curr_count;
	int width = 0;

	for (curr_count = *count + 1; format[curr_count] != '\0'; curr_count++)
	{
		if (is_digit(format[curr_count]))
		{
			width *= 10;
			width += format[curr_count] - '0';
		}
		else if (format[curr_count] == '*')
		{
			curr_count++;
			width = va_arg(list, int);
			break;
		}
		else
			break;
	}

	*count = curr_count - 1;

	return (width);
}
