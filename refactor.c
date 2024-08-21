#include "main.h"

void process_format_specifiers(const char **p, int *flags, int *width, int *precision, int *length)
{
    handle_flags(p, flags);
    handle_width(p, width);
    handle_precision(p, precision);
    handle_length_modifier(p, length);
}

void handle_common_specifiers(const char *p, va_list args, char *buffer, int *index, int flags, int width, int precision)
{
    if (*p == 'd' || *p == 'i')
        convert_int(va_arg(args, int), flags, width, precision, buffer, index);
    else if (*p == 'u' || *p == 'o' || *p == 'x' || *p == 'X')
        convert_unsigned(va_arg(args, unsigned long), get_base(*p), flags, width, precision, buffer, index);
    else if (*p == 'c')
        convert_char(va_arg(args, int), buffer, index);
    else if (*p == 's')
        convert_string(va_arg(args, const char *), buffer, index);
    else if (*p == 'p')
        handle_pointer(args, buffer, index);
}

void handle_custom_specifiers(const char *p, va_list args, char *buffer, int *index)
{
    if (*p == 'b')
        convert_binary(va_arg(args, unsigned long), buffer, index);
    else if (*p == 'S')
        handle_special_string(args, buffer, index);
    else if (*p == 'r')
        handle_reversed_string(args, buffer, index);
    else if (*p == 'R')
        handle_rot13_string(args, buffer, index);
}

void handle_escape_sequence(const char **p, va_list args, char *buffer, int *index)
{
    if (**p == '\\')
    {
        if (*(*p + 1) == 'x')
        {
            convert_nonprintable(va_arg(args, int), buffer, index);
            (*p)++;
        }
    }
}

void handle_unknown_specifier(const char *p, char *buffer, int *index)
{
    buffer[(*index)++] = '%';
    buffer[(*index)++] = *p;
}

