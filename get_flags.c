#include "main.h"

int get_flags(const char *format, int *count)
{
	int j, curr_count;
	int flags = 0;
	const char FLAGS_CH[] = {'-', '+', '0', '#', ' ', '\0'};
	const int FLAGS_ARR[] = {F_MINUS, F_PLUS, F_ZERO, F_HASH, F_SPACE, 0};

	for (curr_count = *count + 1; format[curr_count] != '\0'; curr_count++)
	{
		for (j = 0; FLAGS_CH[j] != '\0'; j++)
			if (format[curr_count] == FLAGS_CH[j])
			{
				flags |= FLAGS_ARR[j];
				break;
			}
		if (FLAGS_CH[j] == 0)
			break;
	}
	*count = curr_count - 1;

	return (flags);
}
