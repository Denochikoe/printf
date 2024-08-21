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

#define FLAG_PLUS       4
#define FLAG_SPACE      8
#define FLAG_HASH       16
#define FLAG_ZERO       1
#define FLAG_MINUS      2

#define LENGTH_LONG     1
#define LENGTH_LONG_LONG 2    /* Add this line */
#define LENGTH_SHORT    3
#define LENGTH_CHAR     4    /* Add this line */

int _printf(const char *format, ...);

void process_specifier(const char *p, va_list args, char *buffer, int *index);
void process_format_specifiers(const char **p, int *flags, int *width, int *precision, int *length);

void handle_common_specifiers(const char *p, va_list args, char *buffer, int *index, int flags, int width, int precision);
void handle_custom_specifiers(const char *p, va_list args, char *buffer, int *index);
void handle_escape_sequence(const char **p, va_list args, char *buffer, int *index);
void handle_unknown_specifier(const char *p, char *buffer, int *index);

void convert_char(char value, char *buffer, int *index);
void convert_string(const char *value, char *buffer, int *index);
void convert_int(int value, int flags, int width, int precision, char *buffer, int *index);
void convert_unsigned(unsigned long value, int base, int flags, int width, int precision, char *buffer, int *index);
void convert_pointer(void *value, char *buffer, int *index);
void convert_binary(unsigned long value, char *buffer, int *index);
void convert_reversed_string(const char *value, char *buffer, int *index);
void convert_rot13_string(const char *value, char *buffer, int *index);

void reverse_str(char *str, int len);
int is_nonprintable(char c);
void convert_nonprintable(char c, char *buffer, int *index);

int get_base(char specifier);

void handle_flags(const char **format, int *flags);
void handle_width(const char **format, int *width);
void handle_precision(const char **format, int *precision);
void handle_length_modifier(const char **format, int *length);

void add_to_buffer(char *buffer, const char *str, int *index);
void add_padding(int len, char pad_char, char *buffer, int *index);
void add_prefix(int base, int flags, unsigned long value, char *buffer, int *index);

void handle_int_flags(int value, int flags, char *buffer, int *index);
int _itoa(long value, char *buffer, int base);

void handle_pointer(va_list args, char *buffer, int *index);
void handle_special_string(va_list args, char *buffer, int *index);
void handle_reversed_string(va_list args, char *buffer, int *index);
void handle_rot13_string(va_list args, char *buffer, int *index);

#endif /* PRINT_H_ */

