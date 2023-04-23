#include "main.h"

/**
 * get_flags - get active flags
 * @format: Formatted string in which to print arguments in
 * @i: take a parameter.
 * Return: flags:
 */
int get_flags(const char *format, int *i)
{
	int j, current_i;
	int flags = 0;
	const char FLAGS_CHAR[] = {'-', '+', '0', '#', ' ', '\0'};
	const int FLAGS_ARRAY[] = {F_MINUS, F_PLUS, F_ZERO, F_HASH, F_SPACE, 0};

	for (current_i = *i + 1; format[current_i] != '\0'; current_i++)
	{
		for (j = 0; FLAGS_CHAR[j] != '\0'; j++)
			if (format[current_i] == FLAGS_CHAR[j])
			{
				flags |= FLAGS_ARRAY[j];
				break;
			}

		if (FLAGS_CHAR[j] == 0)
			break;
	}

	*i = current_i - 1;

	return (flags);
}
/**
 * get_precision - get the precision for printing
 * @format: formatted string in which to print the arguments
 * @list_i: List of arguments to be printed.
 * @args: list of arguments.
 * Return: Precision.
 */
int get_precision(const char *format, int *list_i, va_list args)
{
	int current_i = *list_i + 1;
	int precision = -1;

	if (format[current_i] != '.')
		return (precision);

	precision = 0;

	for (current_i += 1; format[current_i] != '\0'; current_i++)
	{
		if (is_digit(format[current_i]))
		{
			precision *= 10;
			precision += format[current_i] - '0';
		}
		else if (format[current_i] == '*')
		{
			current_i++;
			precision = va_arg(args, int);
			break;
		}
		else
			break;
	}

	*list_i = current_i - 1;

	return (precision);
}


/**
 * get_size - get the size to cast the argument
 * @format: formatted string in which to print the arguments
 * @list_i: list of arguments to be printed.
 * Return: size.
 */
int get_size(const char *format, int *list_i)
{
	int current_i = *list_i + 1;
	int size = 0;

	if (format[current_i] == 'l')
		size = S_LONG;
	else if (format[current_i] == 'h')
		size = S_SHORT;

	if (size == 0)
		*list_i = current_i - 1;
	else
		*list_i = current_i;

	return (size);
}


/**
 * get_width - get the width for printing
 * @format: formatted string in which to print the arguments.
 * @list_i: List of arguments to be printed.
 * @args: list of arguments.
 * Return: width.
 */
int get_width(const char *format, int *list_i, va_list args)
{
	int current_i;
	int width = 0;

	for (current_i = *list_i + 1; format[current_i] != '\0'; current_i++)
	{
		if (is_digit(format[current_i]))
		{
			width *= 10;
			width += format[current_i] - '0';
		}
		else if (format[current_i] == '*')
		{
			current_i++;
			width = va_arg(args, int);
			break;
		}
		else
			break;
	}

	*list_i = current_i - 1;

	return (width);
}
