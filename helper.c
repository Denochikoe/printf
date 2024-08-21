#include "main.h"

int _itoa(long value, char *buffer, int base)
{
    char *ptr = buffer;
    int len = 0;
    unsigned long abs_value = value < 0 ? -value : value;

    do
    {
        *ptr++ = "0123456789ABCDEF"[abs_value % base];
        abs_value /= base;
        len++;
    } while (abs_value);

    if (value < 0 && base == 10)
    {
        *ptr++ = '-';
        len++;
    }

    *ptr = '\0';

    reverse_str(buffer, len);

    return len;
}

void add_to_buffer(char *buffer, const char *str, int *index)
{
    while (*str)
    {
        buffer[(*index)++] = *str++;
    }
}

void add_prefix(int base, int flags, unsigned long value, char *buffer, int *index)
{
    if (flags & FLAG_HASH)
    {
        if (base == 8)
        {
            if (value != 0)
                add_to_buffer(buffer, "0", index);
        }
        else if (base == 16)
        {
            if (value != 0)
                add_to_buffer(buffer, "0x", index);
        }
    }
}

void add_padding(int len, char pad_char, char *buffer, int *index)
{
    while (len-- > 0)
    {
        buffer[(*index)++] = pad_char;
    }
}

void reverse_str(char *str, int len)
{
    int i;
    char temp;

    for (i = 0; i < len / 2; i++)
    {
        temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
}
