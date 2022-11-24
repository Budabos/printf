#include "main.h"

void print_buffer(char buffer[], int *bufferIndex)
{
	if (*bufferIndex > 0)
		write(1, &buffer[0], *bufferIndex);
	*bufferIndex = 0;
}
int _printf( const char *format, ...)
{
	//dec
	int count;
	int prted =0;
	int prtedChars = 0;
	int flags = 0;
	int width = 0;
	int precision = 0;
	int size = 0;
	int bufferIndex = 0;
	char buffer[BUFFER_SIZE];

	va_list ap;
	va_start(ap,format);

	if (format == NULL)
		return (-1);

	for (count = 0; format && format[count] != '\0'; count++)
	{
		if (format[count] != '%')
		{
			buffer[bufferIndex++] = format[count];
			if (bufferIndex == BUFFER_SIZE)
				print_buffer(buffer, &bufferIndex);
			prtedChars++;
		}
		else
		{
			print_buffer(buffer, &bufferIndex);
			flags = get_flags(format, &count);
			width = get_width(format, &count, ap);
			precision = get_precision(format, &count ,ap);
			size  = get_size(format, &count);
			++count;
			prted = handle_print(format, &count, ap, buffer, flags, width, precision, size);

			if (prted == -1)
				return (-1);
			prtedChars += prted;
		}
	}
print_buffer(buffer, &bufferIndex);
va_end(ap);

return (prtedChars);
}
