#include "main.h"

/**
 * print_charcter - print a single character
 * @args: list a of arguments
 * @buffer: buffer array to handle print
 * @flags: active flags
 * @width: Width
 * @precision: precision specification
 * @size: size
 * Return: number of characterss printed
 */

int print_character(va_list args, char buffer[],
	int flags, int width, int precision, int size)
{
	char ch = va_arg(args, int);

	return (handle_write_character(ch, buffer, flags, width, precision, size));
}

/**
 * print_string - print a string
 * @args: list a of arguments
 * @buffer: buffer array to handle print
 * @flags: active flags
 * @width: Width
 * @precision: precision specification
 * @size: size
 * Return: number of characterss printed
 */

int print_string(va_list args, char buffer[],
	int flags, int width, int precision, int size)
{
	int length = 0, i;
	char *string = va_arg(args, char *);

	UN_USED(buffer);
	UN_USED(flags);
	UN_USED(width);
	UN_USED(precision);
	UN_USED(size);
	if (string == NULL)
	{
		string = "(null)";
		if (precision >= 6)
			string = "      ";
	}
	while (string[length] != '\0')
		length++;
	if (precision >= 0 && precision < length)
		length = precision;

	if (width > length)
	{
		if (flags & F_MINUS)
		{
			write(1, &string[0], length);
			for (i = width - length; i > 0; i--)
			{
				write(1, " ", 1);
			}
			return (width);
		}
		else
		{
			for (i = width - length; i > 0; i--)
				write(1, " ", 1);
			write(1, &string[0], length);
			return (width);
		}
	}
	return (write(1, string, length));
}

/**
 * print_percent_sign - Prints a percent sign
 * @args: list of arguments
 * @buffer: buffer array to handle print
 * @flags: active flags
 * @width: width.
 * @precision: precision specification
 * @size: size specifier
 * Return: number of characterss printed
 */
int print_percent_sign(va_list args, char buffer[],
	int flags, int width, int precision, int size)
{
	UN_USED(args);
	UN_USED(buffer);
	UN_USED(flags);
	UN_USED(width);
	UN_USED(precision);
	UN_USED(size);
	return (write(1, "%%", 1));
}

/**
 * print_int - print an integer
 * @args: list of arguments
 * @buffer: buffer array to handle print
 * @flags: active flags
 * @width: width.
 * @precision: precision specification
 * @size: size specifier
 * Return: Number of chars printed
 */
int print_int(va_list args, char buffer[],
	int flags, int width, int precision, int size)
{
	int i = BUFFER_SIZE - 2;
	int is_negative = 0;
	long int n = va_arg(args, long int);
	unsigned long int num;

	n = convert_size_num(n, size);
	if (n == 0)
	{
		buffer[i--] = '0';
	}
	buffer[BUFFER_SIZE - 1] = '\0';
	num = (unsigned long int)n;
	if (n < 0)
	{
		num = (unsigned long int)((-1) * n);
		is_negative = 1;
	}
	while (num > 0)
	{
		buffer[i--] = (num % 10) + '0';
		num = num / 10;
	}
	i++;
	return (write_number(is_negative, i, buffer, flags, width, precision, size));
}

/**
 * print_binary_num - prints an unsigned number
 * @args: list of arguments
 * @buffer: buffer array to handle print
 * @flags: active flags
 * @width: width.
 * @precision: precision specification
 * @size: size
 * Return: numbers of chars.
 */
int print_binary_num(va_list args, char buffer[],
	int flags, int width, int precision, int size)
{
	unsigned int n, m, i, sum;
	unsigned int a[32];
	int count;

	UN_USED(buffer);
	UN_USED(flags);
	UN_USED(width);
	UN_USED(precision);
	UN_USED(size);
	n = va_arg(args, unsigned int);
	m = 2147483648;
	a[0] = n / m;
	for (i = 1; i < 32; i++)
	{
		m /= 2;
		a[i] = (n / m) % 2;
	}
	for (i = 0, sum = 0, count = 0; i < 32; i++)
	{
		sum += a[i];
		if (sum || i == 31)
		{
			char z = '0' + a[i];

			write(1, &z, 1);
			count++;
		}
	}
	return (count);
}
