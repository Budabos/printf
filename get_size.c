#include "main.h"

int get_size(const char *format, int *count)
{
	int curr_count = *count + 1;
	int size = 0;

	if (format[curr_count] == 'l')
		size = S_LONG;
	else if (format[curr_count] == 'h')
		size = S_SHORT;

	if (size == 0)
		*count = curr_count - 1;
	else
		*count = curr_count;
	return (size);
}
