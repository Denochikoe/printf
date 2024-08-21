#include "main.h"

void convert_rot13_string(const char *str, char *buffer, int *index)
{
    while (*str)
    {
        if ((*str >= 'a' && *str <= 'z'))
            buffer[(*index)++] = (*str - 'a' + 13) % 26 + 'a';
        else if ((*str >= 'A' && *str <= 'Z'))
            buffer[(*index)++] = (*str - 'A' + 13) % 26 + 'A';
        else
            buffer[(*index)++] = *str;
        str++;
    }
}

void convert_nonprintable(char c, char *buffer, int *index)
{
    char hex[3];

    buffer[(*index)++] = '\\';
    buffer[(*index)++] = 'x';

    hex[0] = ((c >> 4) & 0xF) + '0';
    if (hex[0] > '9') 
        hex[0] += 7;

    hex[1] = (c & 0xF) + '0';
    if (hex[1] > '9') 
        hex[1] += 7;

    hex[2] = '\0';

    add_to_buffer(buffer, hex, index);
}


void handle_int_flags(int value, int flags, char *buffer, int *index)
{
    if (flags & FLAG_PLUS && value >= 0)
        buffer[(*index)++] = '+';
    else if (flags & FLAG_SPACE && value >= 0)
        buffer[(*index)++] = ' ';
}

int is_nonprintable(char c)
{
    return (c < 32 || c >= 127);
}

void convert_char(char value, char *buffer, int *index) {
    buffer[(*index)++] = value;
}

