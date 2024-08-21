#include "main.h"

void convert_int(int value, int flags, int width, int precision, char *buffer, int *index)
{
    char temp[20];
    int len = 0;

    handle_int_flags(value, flags, buffer, index);

    len = _itoa(value, temp, 10);

    if (precision > len)
        add_padding(precision - len, '0', buffer, index);

    add_to_buffer(buffer, temp, index);

    if (width > len)
        add_padding(width - len, ' ', buffer, index);
}

void convert_unsigned(unsigned long value, int base, int flags, int width, int precision, char *buffer, int *index)
{
    char temp[32];
    int len = 0;

    add_prefix(base, flags, value, buffer, index);

    len = _itoa(value, temp, base);

    if (precision > len)
        add_padding(precision - len, '0', buffer, index);

    add_to_buffer(buffer, temp, index);

    if (width > len)
        add_padding(width - len, ' ', buffer, index);
}

void convert_pointer(void *value, char *buffer, int *index)
{
    add_to_buffer(buffer, "0x", index);

    convert_unsigned((unsigned long)value, 16, 0, 0, 0, buffer, index);
}

void convert_special_string(const char *str, char *buffer, int *index)
{
    while (*str)
    {
        if (is_nonprintable(*str))
            convert_nonprintable(*str, buffer, index);
        else
            buffer[(*index)++] = *str;
        str++;
    }
}

void convert_reversed_string(const char *str, char *buffer, int *index)
{
    int len = strlen(str);
    while (len--)
    {
        buffer[(*index)++] = str[len];
    }
}
