#include "main.h"
/**
 * handle_print_func - Prints an argument based on its type
 * @format: Formatted string in which to print the arguments.
 * @args: List of arguments to be printed.
 * @ind: ind.
 * @buffer: Buffer array to handle print.
 * @flags: Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: 1 or 2;
 */
int handle_print_func(const char *format, int *ind, va_list args,
		char buffer[], int flags, int width, int precision, int size)
{
	int i, un_known_len = 0, printed_chars = -1;
	format_spec_t format_spec[] = {
		{'c', print_character}, {'s', print_string}, {'%', print_percent_sign},
		{'i', print_int}, {'d', print_int}, {'b', print_binary_num},
		{'u', print_unsigned}, {'o', print_octal}, {'x', print_hexadecimal},
		{'X', print_hexa_upper}, {'p', print_pointer}, {'S', print_un_printable},
		{'r', print_rev}, {'R', print_rot13_str}, {'\0', NULL}
	};
	for (i = 0; format_spec[i].spec != '\0'; i++)
		if (format[*ind] == format_spec[i].spec)
			return (format_spec[i].func(args, buffer, flags, width, precision, size));

	if (format_spec[i].spec == '\0')
	{
		if (format[*ind] == '\0')
			return (-1);
		un_known_len += write(1, "%%", 1);
		if (format[*ind - 1] == ' ')
			un_known_len += write(1, " ", 1);
		else if (width)
		{
			--(*ind);
			while (format[*ind] != ' ' && format[*ind] != '%')
				--(*ind);
			if (format[*ind] == ' ')
				--(*ind);
			return (1);
		}
		un_known_len += write(1, &format[*ind], 1);
		return (un_known_len);
	}
	return (printed_chars);
}
