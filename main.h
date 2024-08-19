#ifndef PRINT_H_
#define PRINT_H_

#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

#define FLAG_PLUS	4
#define FLAG_SPACE	8
#define FLAG_HASH	16
#define FLAG_ZERO	1
#define FLAG_MINUS	2
#define FLAG_ZERO_PADDING 1
#define FLAG_UPPER 32

#define LENGTH_LONG	1
#define LENGTH_LONG_LONG 2
#define LENGTH_SHORT	3
#define LENGTH_CHAR	4

/**
 * _printf - Custom print function similar to printf.
 * @format: The format string containing the text to
 * be printed. It can include format specifiers that
 * start with '%'. Supported specifiers include standard
 * and custom ones. For example: %d for intergers, %s for
 * strings, %b for binary.
 * @...: Variable arguments corresponding to the format
 * specifiers.
 *
 * Description: This function processes the format string,
 * handles format specifiers, and prints the formatted
 * output to the standard output. It supports various 
 * format specifiers including custom ones defined by
 * the user.
 *
 * Return: void
 */
int _printf(const char *format, ...);

void convert_char(char value, char *buffer, int *index);
void convert_string(const char *value, char *buffer, int *index);
void convert_int(int value, int flags, int width, int precision, char *buffer, int *index);
void convert_unsigned(unsigned long value, int base, int flags,  int width, int precision, char *buffer, int *index);
void convert_pointer(void *value, char *buffer, int *index);
void convert_binary(unsigned long value, char *buffer, int *index);
void handle_nonprintable(char value, char *buffer, int *index);
void convert_reversed_string(const char *value, char *buffer, int *index);
void convert_rot13_string(const char *value, char *buffer, int *index);

void handle_flags(const char **format, int *flags);
void handle_width(const char **format, int *width);
void handle_precision(const char **format, int *precision);
void handle_length_modifier(const char **format, int *length);
#endif /* PRINT_H_ */
