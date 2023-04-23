#include "main.h"

/**
 * print_unsigned - print the unsigned numbers
 * @args: list of arguments
 * @buffer: the buffer to print its content
 * @flags: active flags
 * @width: width of spaces needed
 * @precision: number of digits after decimal point (ex:.2)
 * @size: size specifier
 * Return: number of characters printed
 */
int print_unsigned(va_list args, char buffer[],
	int flags, int width, int precision, int size)
{
	int i = BUFFER_SIZE - 2;
	unsigned long int number = va_arg(args, unsigned long int);

	number = convert_unsigned_num(number, size);

	if (number == 0)
	{
		buffer[i--] = '0';
	}

	buffer[BUFFER_SIZE - 1] = '\0';

	while (number > 0)
	{
		buffer[i--] = (number % 10) + '0';
		number = number / 10;
	}
	i++;
	return (write_unsigned_num(0, i, buffer, flags, width, precision, size));
}
/**
 * print_octal - print number in octal notation
 * @args: list of arguments
 * @buffer: contain string to be printed
 * @flags: active flags
 * @width: space needed
 * @precision: number of digits after point
 * @size: get size
 * Return: number of characters printed
 */
int print_octal(va_list args, char buffer[],
	int flags, int width, int precision, int size)
{
	int i = BUFFER_SIZE - 2;
	unsigned long int number = va_arg(args, unsigned long int);
	unsigned long int initial_number = number;

	UN_USED(width);

	number = convert_unsigned_num(number, size);

	if (number == 0)
	{
		buffer[i--] = '0';
	}
	buffer[BUFFER_SIZE - 1] = '\0';

	while (number > 0)
	{
		buffer[i--] = (number % 8) + '0';
		number = number / 8;
	}
	if (flags && F_HASH && initial_number != 0)
	{
		buffer[i--] = '0';
	}
	i++;
	return (write_unsigned_num(0, i, buffer, flags, width, precision, size));

}

/**
 * print_hexadecimal - print number in hexadecimal notation
 * @args: list of arguments
 * @buffer: contain string to be printed
 * @flags: active flags
 * @width: space needed
 * @precision: number of digits after point
 * @size: get size
 * Return: number of characters printed
 */
int print_hexadecimal(va_list args, char buffer[],
	int flags, int width, int precision, int size)
{
	return (print_hexa(args, "0123456789abcdef", buffer,
				flags, 'x', width, precision, size));
}

/**
 * print_hexa_upper - print number in upper hexadecimal notation
 * @args: list of arguments
 * @buffer: contain string to be printed
 * @flags: active flags
 * @width: space needed
 * @precision: number of digits after point
 * @size: get size
 * Return: number of characters printed
 */

int print_hexa_upper(va_list args, char buffer[],
	int flags, int width, int precision, int size)
{
	return (print_hexa(args, "0123456789ABCDEF", buffer,
		flags, 'X', width, precision, size));
}
/**
 * print_hexa - print number in hexadecimal(upper / lower) notation
 * @args: list of arguments
 * @map_to: array of numbers to map the number to
 * @buffer: contain string to be printed
 * @flags: active flags
 * @flag_char: active flag either x or X
 * @width: space needed
 * @precision: number of digits after point
 * @size: get size
 * Return: number of characters printed
 */
int print_hexa(va_list args, char map_to[], char buffer[],
	int flags, char flag_char, int width, int precision, int size)
{
	int i = BUFFER_SIZE - 2;
	unsigned long int number = va_arg(args, unsigned long int);
	unsigned long int initial_number = number;

	UN_USED(width);

	if (number == 0)
	{
		buffer[i--] = '0';
	}
	buffer[BUFFER_SIZE - 1] = '\0';

	while (number > 0)
	{
		buffer[i--] = map_to[number % 16];
		number = number / 16;
	}

	if (flags && F_HASH && initial_number != 0)
	{
		buffer[i--] = flag_char;
		buffer[i--] = '0';
	}
	i++;
	return (write_unsigned_num(0, i, buffer, flags, width, precision, size));
}
