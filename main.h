#ifndef MAIN_H
#define MAIN_H
#include <stdio.h>
#include <limits.h>
#include <stdarg.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 1024
#define UN_USED(x) (void)(x)
#define S_LONG 2
#define S_SHORT 1

/**
 * struct format_spec - get suitable function to each specifier
 * @spec: the format specifier
 * @func: the corresponding function
 */

typedef struct format_spec
{
	char spec;
	int (*func)(va_list, char[], int, int, int, int);
} format_spec_t;



/* FLAGS */
#define F_MINUS 1
#define F_PLUS 2
#define F_ZERO 4
#define F_HASH 8
#define F_SPACE 16

int _printf(const char *format, ...);

int handle_print_func(const char *format, int *buffer_index, va_list list_args,
		char buffer[], int flags, int width, int precision, int size);


int print_unsigned(va_list args, char buffer[],
	int flags, int width, int precision, int size);
int print_octal(va_list args, char buffer[],
	int flags, int width, int precision, int size);
int print_hexadecimal(va_list args, char buffer[],
	int flags, int width, int precision, int size);
int print_hexa_upper(va_list args, char buffer[],
	int flags, int width, int precision, int size);
int print_hexa(va_list args, char map_to[], char buffer[],
	int flags, char flag_ch, int width, int precision, int size);

long int convert_unsigned_num(unsigned long int, int);
long int convert_size_num(long int num, int size);

int write_unsigned_num(int is_negative, int ind,
		char buffer[], int flags, int width, int precision, int size);
int handle_write_character(char, char buffer[],
		int flags, int width, int precision, int size);
int write_number(int is_positive, int ind, char buffer[],
		int flags, int width, int precision, int size);
int write_pointer(char buffer[], int index, int length,
		int width, int flags, char padding, char extra_char, int padding_start);
int write_num(int ind, char buffer[], int flags, int width, int precision,
		int length, char padding, char extra_char);



int print_pointer(va_list args, char buffer[],
		int flags, int width, int precision, int size);
int print_un_printable(va_list args, char buffer[],
		int flags, int width, int precision, int size);
int print_rev(va_list args, char buffer[],
		int flags, int width, int precision, int size);
int print_rot13_str(va_list args, char buffer[],
		int flags, int width, int precision, int size);

int print_character(va_list args, char buffer[],
		int flags, int width, int precision, int size);
int print_string(va_list args, char buffer[],
		int flags, int width, int precision, int size);
int print_percent_sign(va_list args, char buffer[],
		int flags, int width, int precision, int size);
int print_int(va_list args, char buffer[],
		int flags, int width, int precision, int size);
int print_binary_num(va_list args, char buffer[],
		int flags, int width, int precision, int size);

int get_width(const char *format, int *list_i, va_list args);
int get_flags(const char *format, int *i);
int get_size(const char *format, int *list_i);
int get_precision(const char *format, int *list_i, va_list args);

int is_printable(char ch);
int append_hexa_code(char ascii_code, char buffer[], int i);
int is_digit(char c);
long int convert_size_num(long int num, int size);
long int convert_unsigned_num(unsigned long int num, int size);

#endif
