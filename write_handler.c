#include "main.h"

/**
 *handle_write_char - this holds char var
 *@c: parameter
 *@buffer: parameter arr
 *@flags: holds flags passed to the fn
 *@width: holds width passed
 *@precision: holds precision
 *@size: holds size
 *Return: an int
 */

int handle_write_char(char c, char buffer[],
	int flags, int width, int precision, int size)
{
	int count = 0;
	char paddIndex = ' ';

	UNUSED(precision);
	UNUSED(size);

	if (flags & F_ZERO)
		paddIndex = '0';

	buffer[count++] = c;
	buffer[count] = '\0';

	if (width > 1)
	{
		buffer[BUFFER_SIZE - 1] = '\0';
		for (count = 0; count < width - 1; count++)
			buffer[BUFFER_SIZE - count - 2] = paddIndex;

		if (flags & F_MINUS)
			return (write(1, &buffer[0], 1) +
					write(1, &buffer[BUFFER_SIZE - count - 1], width - 1));
		else
			return (write(1, &buffer[BUFFER_SIZE - count - 1], width - 1) +
					write(1, &buffer[0], 1));
	}
	return (write(1, &buffer[0], 1));
}

/*****************************************/
/*write_number function*/
/**
 *write_number - it writes number
 *@is_negative: Is a bool
 *@ind: an index
 *@buffer: an arr
 *@flags: holds flags
 *@width: holds width
 *@precision: precision
 *@size: holds size to be pritted
 *Return: an int
 */
int write_number(int is_negative, int ind, char buffer[],
	int flags, int width, int precision, int size)
{
	int len = BUFFER_SIZE - ind - 1;
	char paddIndex = ' ', extra_ch = 0;

	UNUSED(size);

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		paddIndex = '0';
	if (is_negative)
		extra_ch = '-';
	else if (flags & F_PLUS)
		extra_ch = '+';
	else if (flags & F_SPACE)
		extra_ch = ' ';

	return (write_num(ind, buffer, flags, width, precision,
		len, paddIndex, extra_ch));
}

/**************************************/
/*write_num*/
/**
 *write_num - write number
 *@ind: index
 *@buffer: array
 *@flags: olds flags
 *@width: holds width
 *@prec: holds precision
 *@len: thhel length
 *@paddIndex: padd index
 *@extra_c: extra char
 *Return: an int
 */
int write_num(int ind, char buffer[], int flags, int width,
int prec, int len, char paddIndex, char extra_c)
{
	int count;
	int padd_start = 1;

	if (prec == 0 && ind == BUFFER_SIZE - 2 && buffer[ind] == '0' && width == 0)
		return (0);
	if (prec == 0 && ind == BUFFER_SIZE - 2 && buffer[ind] == '0')
		buffer[ind] = paddIndex = ' ';
	if (prec > 0 && prec < len)
		paddIndex = ' ';
	while (prec > len)
		buffer[--ind] = '0', len++;
	if (extra_c != 0)
		len++;
	if (width > len)
	{
		for (count = 1; count < width - len + 1; count++)
			buffer[count] = paddIndex;
		buffer[count] = '\0';
		if (flags & F_MINUS && paddIndex == ' ')
		{
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[ind], len) + write(1, &buffer[1], count - 1));
		}
		else if (!(flags & F_MINUS) && paddIndex == ' ')
		{
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[1], count - 1) + write(1, &buffer[ind], len));
		}
		else if (!(flags & F_MINUS) && paddIndex == '0')
		{
			if (extra_c)
				buffer[--padd_start] = extra_c;
			return (write(1, &buffer[padd_start], count - padd_start) +
				write(1, &buffer[ind], len - (1 - padd_start)));
		}
	}
	if (extra_c)
		buffer[--ind] = extra_c;
	return (write(1, &buffer[ind], len));
}

/*****************************************/
/*write_unsgnd*/
/**
 *write_unsgnd - prints unsigned
 *@is_negative: a bool
 *@ind: index
 *@buffer: an array of element
 *@flags: olds flags
 *@width: holds width
 *@precision: olds precison
 *@size: holds size
 *Return: an int
 */
int write_unsgnd(int is_negative, int ind,
	char buffer[],
	int flags, int width, int precision, int size)
{
	int len = BUFFER_SIZE - ind - 1;
	int count = 0;
	char paddIndex = ' ';

	UNUSED(is_negative);
	UNUSED(size);

	if (precision == 0 && ind == BUFFER_SIZE - 2 && buffer[ind] == '0')
		return (0);

	if (precision > 0 && precision < len)
		paddIndex = ' ';

	while (precision > len)
	{
		buffer[--ind] = '0';
		len++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		paddIndex = '0';

	if (width > len)
	{
		for (count = 0; count < width - len; count++)
			buffer[count] = paddIndex;

		buffer[count] = '\0';

		if (flags & F_MINUS)
		{
			return (write(1, &buffer[ind], len) + write(1, &buffer[0], count));
		}
		else
		{
			return (write(1, &buffer[0], count) + write(1, &buffer[ind], len));
		}
	}

	return (write(1, &buffer[ind], len));
}
/****************************************/
/*write_pointer*/
/**
 *write_pointer - writes pointer
 *@buffer: an array
 *@ind: index
 *@len: length
 *@width: olds width
 *@flags: holds flags
 *@paddIndex: padd index
 *@extra_c: extra car
 *@padd_start: padd satrt
 *Return: an iter
 */
int write_pointer(char buffer[], int ind, int len,
	int width, int flags, char paddIndex, char extra_c, int padd_start)
{
	int count;

	if (width > len)
	{
		for (count = 3; count < width - len + 3; count++)
			buffer[count] = paddIndex;
		buffer[count] = '\0';
		if (flags & F_MINUS && paddIndex == ' ')
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[ind], len) + write(1, &buffer[3], count - 3));
		}
		else if (!(flags & F_MINUS) && paddIndex == ' ')
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[3], count - 3) + write(1, &buffer[ind], len));
		}
		else if (!(flags & F_MINUS) && paddIndex == '0')
		{
			if (extra_c)
				buffer[--padd_start] = extra_c;
			buffer[1] = '0';
			buffer[2] = 'x';
			return (write(1, &buffer[padd_start], count - padd_start) +
				write(1, &buffer[ind], len - (1 - padd_start) - 2));
		}
	}
	buffer[--ind] = 'x';
	buffer[--ind] = '0';
	if (extra_c)
		buffer[--ind] = extra_c;
	return (write(1, &buffer[ind], BUFFER_SIZE - ind - 1));
}
