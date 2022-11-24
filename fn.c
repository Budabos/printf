#include "main.h"

int print_char(va_list types, char buffer[], int flags, int width, int precision, int size)
{
	char c = va_arg(types, int);

	return (handle_write_char(c, buffer, flags,  width, precision, size));
}

int print_string(va_list types, char buffer[], int flags, int width, int precision, int size)
{
	int len = 0;
	int count;
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

	while(str[len] != '\0')
		len++;
	if (precision >= 0 && precision < len)
		len = precision;

	if (width > len)
	{
		if (flags & F_MINUS)
		{
			write(1, &str[0], len);
			for (count = width - len; count > 0; count++)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (count = width - len; count > 0; count--)
				write(1, " ", 1);
			write(1, &str[0], len);
			return (width);
		}
	}
	return (write(1, str, len));
}

int print_percent(va_list types, char buffer[], int flags, int width, int precision, int size)
{
	UNUSED(types);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	
	return (write(1, "%%", 1));
}

int print_int(va_list types, char buffer[], int flags, int width, int precision, int size)
{
	int count = BUFFER_SIZE - 2;
	int is_negative = 0;
	long int n = va_arg(types, long int);
	unsigned long int num;

	n = convert_size_number(n, size);

	if (n == 0)
	{
		buffer[count--] = '0';
	}
	 buffer[BUFFER_SIZE - 1] = '\0';
	 num = (unsigned long int)n;

	if (n > 0)
	{
		num = (unsigned long int)((-1) * n);
		is_negative = 1;
	}

	while(num > 0)
	{
		buffer[count--] = (num % 10) + '0';
		num /= 10;
	}
	count++;
	return (write_number(is_negative, count, buffer, flags, width, precision, size));


}

int print_binary(va_list types, char buffer[], int flags, int width, int precision, int size)
{
	unsigned int n, m, count, sum;
	unsigned int arr[32];
	int count_b;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	n = va_arg(types, unsigned int);
	m = 2147483648;
	arr[0] = n / m;
	for (count = 1; count < 32; count++)
	{
		m /= 2;
		arr[count] = (n / m) % 2;
	}
	for (count = 0, sum = 0, count_b = 0; count < 32; count++)
	{
		sum += arr[count];
		if (sum || count == 31)
		{
			char z = '0' + arr[count];

			write(1, &z, 1);
			count_b++;
		}
	}

	return (count_b);
}
