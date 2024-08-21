#include "main.h"

void handle_reversed_string(va_list args, char *buffer, int *index) {
    const char *str = va_arg(args, const char *);
    int len = strlen(str);
    int i;
    for (i = len - 1; i >= 0; i--) {
        buffer[(*index)++] = str[i];
    }
}

void handle_rot13_string(va_list args, char *buffer, int *index) {
    const char *str = va_arg(args, const char *);
    while (*str) {
        char c = *str;
        if (c >= 'a' && c <= 'z') {
            buffer[(*index)++] = ((c - 'a' + 13) % 26) + 'a';
        } else if (c >= 'A' && c <= 'Z') {
            buffer[(*index)++] = ((c - 'A' + 13) % 26) + 'A';
        } else {
            buffer[(*index)++] = c;
        }
        str++;
    }
}
