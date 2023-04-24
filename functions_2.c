#include "main.h"
/**
 * print_pointer - print value of pointer var
 * @args: list of arguments
 * @buffer: buffr array to be printed
 * @flags: active flags
 * @width: space needed
 * @precision: precision specification
 * @size: size
 * Return: number of characters printed
 */
int print_pointer(va_list args, char buffer[],
	int flags, int width, int precision, int size)
{
	char extra_char = 0, padding = ' ';
	int index = BUFFER_SIZE - 2, length = 2, padding_start = 1;
	unsigned long number_address;
	char map_to[] = "0123456789abcdef";
	void *address = va_arg(args, void *);

	UN_USED(width);
	UN_USED(size);
	if (address == NULL)
	{
		return (write(1, "(nil)", 5));
	}
	buffer[BUFFER_SIZE - 1] = '\0';
	UN_USED(precision);
	number_address = (unsigned long)address;
	while (number_address > 0)
	{
		buffer[index--] = map_to[number_address % 16];
		number_address /= 16;
		length++;
	}
	if ((flags & F_ZERO) && !(flags & F_MINUS))
	{
		padding = '0';
	}
	if (flags & F_PLUS)
	{
		extra_char = '+', length++;
	}
	else if (flags & F_SPACE)
	{
		extra_char = ' ', length++;
	}
	index++;
	return (write_pointer(buffer, index, length,
		width, flags, padding, extra_char, padding_start));
}

/**
 * print_un_printable - print ASCII code in hexa
 * @args: list of arguments
 * @buffer: buff array to be printed
 * @flags: active flags
 * @width: space needed
 * @precision: precision specification
 * @size: size
 * Return: number of characters printed
 */

int print_un_printable(va_list args, char buffer[],
	int flags, int width, int precision, int size)
{
	int i = 0, off_set = 0;
	char *string = va_arg(args, char *);

	UN_USED(flags);
	UN_USED(precision);
	UN_USED(size);
	UN_USED(width);
	if (string == NULL)
	{
		return (write(1, "(null)", 6));
	}
	while (string[i] != '\0')
	{
		if (is_printable(string[i]))
		{
			buffer[i + off_set] = string[i];
		}
		else
		{
			off_set += append_hexa_code(string[i], buffer, i + off_set);
		}
		i++;
	}
	buffer[i + off_set] = '\0';
	return (write(1, buffer, i + off_set));
}

/**
 * print_rev - print reversed string
 * @args: list of arguments
 * @buffer: buffer array to be printed
 * @flags: active flags
 * @width: space needed
 * @precision: precision specification
 * @size: size
 * Return: number of characters printed
 */
int print_rev(va_list args, char buffer[],
	int flags, int width, int precision, int size)
{
	char *string;
	int i = 0, count = 0;

	UN_USED(width);
	UN_USED(buffer);
	UN_USED(flags);
	UN_USED(size);

	string = va_arg(args, char *);

	if (string == NULL)
	{
		UN_USED(precision);

		string = ")Null(";
	}
	for (i = 0; string[i]; i++)
	{
		;
	}

	for (i = i - 1; i >= 0; i--)
	{
		char z = string[i];

		write(1, &z, 1);
		count++;
	}
	return (count);
}

/**
 * print_rot13_str - print string in ROT13
 * @args: list of arguments
 * @buffer: buffer array to be printed
 * @flags: active flags
 * @width: space needed
 * @precision: precision specification
 * @size: size
 * Return: number of characters printed
 */
int print_rot13_str(va_list args, char buffer[],
	int flags, int width, int precision, int size)
{
	char x;
	char *string;
	unsigned int i, j;
	int count = 0;
	char in_side[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char out_side[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	string = va_arg(args, char *);
	UN_USED(buffer);
	UN_USED(flags);
	UN_USED(width);
	UN_USED(precision);
	UN_USED(size);

	if (string == NULL)
	{
		string = "(AHYY)";
	}
	for (i = 0; string[i]; i++)
	{
		for (j = 0; in_side[j]; j++)
		{
			if (in_side[j] == string[i])
			{
				x = out_side[j];
				write(1, &x, 1);
				count++;
				break;
			}
		}
		if (!in_side[j])
		{
			x = string[i];
			write(1, &x, 1);
			count++;
		}
	}
	return (count);
}
