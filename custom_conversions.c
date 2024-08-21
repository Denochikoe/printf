#include "main.h"

/**
 * handle_nonprintable - Handles non-printable characters by
 * converting them to a hexadecimal representation and storing
 * in buffer.
 * @value: The character to be checked and possibly converted.
 * @buffer: The buffer to store the output string.
 * @index: Pointer to the current index in the buffer.
 *
 * Description: This function checks if a character is
 * non-printable (less than ASCII 32 or greater than or equal
 * to 127). If it is non-printable, the function converts it
 * into a hexadecimal format and stores it in the buffer.
 * If the character is printable, it is stored as is in the
 * buffer.
 * Return: void
 */
void handle_nonprintable(char value, char *buffer, int *index)
{
	if (value < 32 || value >= 127)
	{
		snprintf(&buffer[*index], 5, "\\x%02X", (unsigned char)value);
		*index += 4;
	}
	else
	{
		buffer[(*index)++] = value;
	}
}

void convert_string(const char *value, char *buffer, int *index) {
    while (*value) {
        buffer[(*index)++] = *value++;
    }
}

void handle_pointer(va_list args, char *buffer, int *index) {
    void *ptr = va_arg(args, void *);
    unsigned long address = (unsigned long)ptr;
    char temp[20];
    int len = sprintf(temp, "0x%lx", address);
    memcpy(buffer + *index, temp, len);
    *index += len;
}

void convert_binary(unsigned long value, char *buffer, int *index) {
    char temp[65];
    int i = 0;
    if (value == 0) {
        buffer[(*index)++] = '0';
        return;
    }
    while (value > 0) {
        temp[i++] = (value & 1) ? '1' : '0';
        value >>= 1;
    }
    while (i > 0) {
        buffer[(*index)++] = temp[--i];
    }
}

void handle_special_string(va_list args, char *buffer, int *index) {
    const char *str = va_arg(args, const char *);
    while (*str) {
        if (*str == '\n') {
            buffer[(*index)++] = '\\';
            buffer[(*index)++] = 'n';
        } else if (*str == '\t') {
            buffer[(*index)++] = '\\';
            buffer[(*index)++] = 't';
        } else {
            buffer[(*index)++] = *str;
        }
        str++;
    }
}
