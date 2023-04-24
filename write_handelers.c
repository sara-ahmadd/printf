#include "main.h"

/**
 * handle_write_charcter- prints a string
 * @c: char types.
 * @buffer: Buffer array to handle print
 * @flags:  active flags.
 * @width: get width.
 * @precision: precision specifier
 * @size: size
 * Return: Number of chars printed.
 */
int handle_write_character(char c, char buffer[],
	int flags, int width, int precision, int size)
{
	int i = 0;
	char padding = ' ';

	UN_USED(precision);
	UN_USED(size);

	if (flags & F_ZERO)
		padding = '0';

	buffer[i++] = c;
	buffer[i] = '\0';

	if (width > 1)
	{
		buffer[BUFFER_SIZE - 1] = '\0';
		for (i = 0; i < width - 1; i++)
			buffer[BUFFER_SIZE - i - 2] = padding;

		if (flags & F_MINUS)
			return (write(1, buffer, 1) +
					write(1, &buffer[BUFFER_SIZE - i - 1], width - 1));
		else
			return (write(1, &buffer[BUFFER_SIZE - i - 1], width - 1) +
					write(1, buffer, 1));
	}

	return (write(1, buffer, 1));
}
/**
 * write_number - Prints a number
 * @is_negative: List of arguments
 * @ind: index.
 * @buffer: buffer array to handle print
 * @flags:  active flags
 * @width: get width.
 * @precision: precision specifier
 * @size: size specifier
 * Return: Number of chars printed.
 */
int write_number(int is_negative, int ind, char buffer[],
	int flags, int width, int precision, int size)
{
	int length = BUFFER_SIZE - ind - 1;
	char padding = ' ', extra_char = 0;

	UN_USED(size);

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padding = '0';
	if (is_negative)
		extra_char = '-';
	else if (flags & F_PLUS)
		extra_char = '+';
	else if (flags & F_SPACE)
		extra_char = ' ';

	return (write_num(ind, buffer, flags, width, precision,
				length, padding, extra_char));
}


/**
 * write_num - write number using  buffer
 * @ind: Index at which the number starts on the buffer
 * @buffer: Buffer
 * @flags: Flags
 * @width: width
 * @precision: Precision specifier
 * @length: Number length
 * @padding: padding char
 * @extra_char: extra char
 * Return: Number of printed chars.
 */
int write_num(int ind, char buffer[], int flags, int width,
		int precision, int length, char padding, char extra_char)
{
	int i, padding_start = 1;

	if (precision == 0 && ind == BUFFER_SIZE - 2
			&& buffer[ind] == '0' && width == 0)
		return (0);
	if (precision == 0 && ind == BUFFER_SIZE - 2 && buffer[ind] == '0')
		buffer[ind] = padding = ' ';
	if (precision > 0 && precision < length)
		padding = ' ';
	while (precision > length)
		buffer[--ind] = '0', length++;
	if (extra_char != 0)
		length++;
	if (width > length)
	{
		for (i = 1; i < width - length + 1; i++)
			buffer[i] = padding;
		buffer[i] = '\0';
		if (flags & F_MINUS && padding == ' ')
		{
			if (extra_char)
				buffer[--ind] = extra_char;
			return (write(1, &buffer[ind], length) + write(1, &buffer[1], i - 1));
		}
		else if (!(flags & F_MINUS) && padding == ' ')
		{
			if (extra_char)
				buffer[--ind] = extra_char;
			return (write(1, &buffer[1], i - 1) + write(1, &buffer[ind], length));
		}
		else if (!(flags & F_MINUS) && padding == '0')
		{
			if (extra_char)
				buffer[--padding_start] = extra_char;
			return (write(1, &buffer[padding_start], i - padding_start) +
					write(1, &buffer[ind], length - (1 - padding_start)));
		}
	}
	extra_char && buffer[--ind] = extra_char;
	return (write(1, &buffer[ind], length));
}

/**
 * write_unsigned_num - Writes an unsigned number
 * @is_negative: Number indicating if the num is negative
 * @ind: Index at which the number starts in the buffer
 * @buffer: Array of chars
 * @flags: Flags
 * @width: Width
 * @precision: Precision
 * @size: Size
 * Return: Number of written chars.
 */
int write_unsigned_num(int is_negative, int ind,
		char buffer[], int flags, int width, int precision, int size)
{
	int length = BUFFER_SIZE - ind - 1, i = 0;
	char padding = ' ';

	UN_USED(is_negative);
	UN_USED(size);
	if (precision == 0 && ind == BUFFER_SIZE - 2 && buffer[ind] == '0')
		return (0);
	if (precision > 0 && precision < length)
		padding = ' ';
	while (precision > length)
	{
		buffer[--ind] = '0';
		length++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padding = '0';
	if (width > length)
	{
		for (i = 0; i < width - length; i++)
			buffer[i] = padding;
		buffer[i] = '\0';
		if (flags & F_MINUS)
		{
			return (write(1, &buffer[ind], length) + write(1, &buffer[0], i));
		}
		else
		{
			return (write(1, &buffer[0], i) + write(1, &buffer[ind], length));
		}
	}
	return (write(1, &buffer[ind], length));
}

/**
 * write_pointer - write memory address
 * @buffer: buffer array of chars
 * @ind: Index at which the number starts in the buffer
 * @length: length of number
 * @width: width
 * @flags: flags
 * @padding: character representing the padding
 * @extra_char: character representing extra char
 * @padding_start: index at which padding should start
 * Return: Number of written chars.
 */
int write_pointer(char buffer[], int ind, int length,
	int width, int flags, char padding, char extra_char, int padding_start)
{
	int i;

	if (width > length)
	{
		for (i = 3; i < width - length + 3; i++)
			buffer[i] = padding;
		buffer[i] = '\0';
		if (flags & F_MINUS && padding == ' ')
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (extra_char)
			{
				buffer[--ind] = extra_char;
			}
			return (write(1, &buffer[ind], length) + write(1, &buffer[3], i - 3));
		}
		else if (!(flags & F_MINUS) && padding == ' ')
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (extra_char)
			{
				buffer[--ind] = extra_char;
			}
			return (write(1, &buffer[3], i - 3) + write(1, &buffer[ind], length));
		}
		else if (!(flags & F_MINUS) && padding == '0')
		{
			if (extra_char)
			{
				buffer[--padding_start] = extra_char;
			}
			buffer[1] = '0';
			buffer[2] = 'x';
			return (write(1, &buffer[padding_start], i - padding_start) +
				write(1, &buffer[ind], length - (1 - padding_start) - 2));
		}
	}
	buffer[--ind] = 'x';
	buffer[--ind] = '0';
	extra_char && buffer[--ind] = extra_char;
	return (write(1, &buffer[ind], BUFFER_SIZE - ind - 1));
}
