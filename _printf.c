#include "main.h"

void print_buffer(char buffer[], int *buffer_index);
/**
 * _printf - print string to terminal
 * @format: the string input
 * Return: number pf printed characters to the screen
 */
int _printf(const char *format, ...)
{
	int i, printed_characters = 0, characters_handeled = 0;
	int width, precision, size, flags, buffer_index = 0;
	va_list args;
	char buffer[BUFFER_SIZE];

	va_start(args, format);

	if (format)
	{
		for (i = 0; format[i] != '\0'; i++)
		{
			if (format[i] != '%')
			{
				buffer[buffer_index] = format[i];

				if (buffer_index == BUFFER_SIZE)
				{
					print_buffer(buffer, &buffer_index);
				}
				printed_characters++;
			}
			else
			{
				print_buffer(buffer, &buffer_index);
				flags = get_flags(format, &i);
				width = get_width(format, &i, args);
				precision = get_precision(format, &i, args);
				size = get_size(format, &i);
				++i;
				characters_handeled = handle_print_func(format, &i, args, buffer,
						flags, width, precision, size);
				if (characters_handeled == -1)
				{
					return (-1);
				}
				printed_characters += characters_handeled;
			}
		}
		print_buffer(buffer, &buffer_index);
		va_end(args);
		return (printed_characters);
	}
	else
	{
		return (-1);
	}
}
/**
 * print_buffer - print content of the buffer
 * @buffer: string content inside buffer
 * @buffer_index: length of the buffer
 */
void print_buffer(char buffer[], int *buffer_index)
{
	if (*buffer_index > 0)
	{
		write(1, buffer, *buffer_index);
	}
	*buffer_index = 0;
}
