#include "main.h"

/**
 * convert_char - Converts a character and stores it in the
 * buffer
 * @value: The character to be converted
 * @buffer: The buffer to store the converted character
 * @index: Pointer to the current index in the buffer
 *
 * Description: This function takes a character, places it in
 * buffer, and updates the index accordingly.
 *
 * Return: void
 */

void convert_char(char value, char *buffer, int *index)
{
	buffer[(*index)++] = value;
}

/**
 * convert_string - Converts a string and stores it in the
 * @value: The string to be converted
 * @buffer: The buffer to store the converted string
 * @index: Pointer to the current index in the buffer
 *
 * Decription: This function takes a string, places each
 * character in the buffer, and handles non-printable
 * characters by converting them into a hexadecimal
 * representation prefixed by '\x'. It updates the
 * buffer index accordingly.
 */
void convert_string(const char *value, char *buffer, int *index)
{
	if (value == NULL || buffer == NULL || index == NULL)
	{
		return;
	}

	while (*value && *index < BUFFER_SIZE - 1)
	{
		if (isprint((unsigned char)*value))
		{
			buffer[(*index)++] = *value++;
		}
		else
		{
			if (*index < BUFFER_SIZE - 4)
			{
				buffer[(*index)++] = '\\';
				buffer[(*index)++] = 'x';

				sprintf(&buffer[*index], "%02X", (unsigned char)*value);
				*index += 2;
			}
			else
			{
				break;
			}
		}
		value++;
	}
	buffer[*index] = '\0';
}

/**
 * convert_int - Converts an integer to a string and stores it
 * in the buffer
 * @value: The integer value to be converted
 * @flags: Formatting flags (e.g., plus, space)
 * @width: Minimum field width for the output
 * @precision: Precision for the output
 * @buffer: The buffer to store the converted string
 * @index: Pointer to the current index in the buffer
 *
 * Description: This function converts an integer into a string
 * based on the specified flags, width, and precision. It
 * handles the '+' and ' ' flags for positive numbers, adjust
 * the width accordingly, and stores the formatted string
 * into the provided buffer.
 *
 * Return: void
 */
void convert_int(int value, int flags, int width, int precision, char *buffer, int *index)
{
	char temp[64];
	int len;
	int i;

	if ((flags & FLAG_PLUS && value >= 0) || (flags & FLAG_SPACE && value >= 0))
	{
		width--;
	}

	len = snprintf(temp, sizeof(temp), "%*.*d", width, precision, value);

	if (value >= 0)
	{
		if (flags & FLAG_PLUS)
		{
			buffer[(*index)++] = '+';
		}
		else if (flags & FLAG_SPACE)
		{
			buffer[(*index)++] = ' ';
		}
	}

	for (i = 0; i < len && *index < BUFFER_SIZE - 1; i++)
	{
		buffer[(*index)++] = temp[i];
	}

	if (*index < BUFFER_SIZE - 1)
	{
		buffer[*index] = '\0';
	}
}

/**
 * convert_unsigned - Converts an unsigned integer to a string
 * in a given base and stores it in the buffer.
 * @value: The unsigned integer value to be converted.
 * @base: The base for conversion (e.g., 10 for decimal, 16
 * for hexadecimal).
 * @flags: Formatting flags (e.g., hash, zero, minus, upper).
 * @width: Minimum field width for the output.
 * @precision: Precision for the output.
 * @buffer: The buffer to store the converted string.
 * @index: Pointer to the current index in the buffer.
 *
 * Description: This function converts an unsigned integer into
 * a string based on the specified base, flags, width, and
 * precision. It handles the '#' for octal and hexadecimal
 * prefixes, '0' flag for padding, and left justification.
 *
 * Return: void
 */ 
void convert_unsigned(unsigned long value, int base, int flags, int width, int precision, char *buffer, int *index)
{
	char temp[BUFFER_SIZE];
	char digits[] = "0123456789abcdef";
	char digits_upper[] = "0123456789ABCDEF";
	int i = 0;
	unsigned long num = value;

	char *digits_to_use = (base == 16 && (flags & FLAG_UPPER)) ? digits_upper : digits;

	if (flags & FLAG_HASH)
	{
		if (base == 8 && value != 0)
		{
			buffer[(*index)++] = '0';
		}
		else if (base == 16 && value != 0)
		{
			buffer[(*index)++] = '0';
			buffer[(*index)++] = (flags & FLAG_UPPER) ? 'X' : 'x';
		}
	}

	do {
		temp[i++] = digits_to_use[num % base];
		num /= base;
	} while (num > 0);

	while (i < precision)
	{
		temp[i++] = '0';
	}

	if (!(flags & FLAG_MINUS) && flags & FLAG_ZERO)
	{
		while (i < width)
		{
			buffer[(*index)++] = '0';
		}
	}

	while (i > 0)
	{
		buffer[(*index)++] = temp[--i];
	}

	while (i < width)
	{
		buffer[(*index)++] = ' ';
		i++;
	}
}

/**
 * convert_binary - Converts an unsigned long value to a binary
 * string and stores it in the buffer
 * @value: The unsigned long value to be converted
 * @buffer: The buffer to store the binary string.
 * @index: Pointer to the current index in the buffer.
 *
 * Description: This function converts an unsigned long integer
 * into a binary string and stores the result in the provided
 * buffer. It handles leading zeros and ensures that the output
 * is within the buffer size limits.
 */
void convert_binary(unsigned long value, char *buffer, int *index)
{
	char temp[65];
	int pos = 0;
	int i;

	if (value == 0)
	{
		temp[pos++] = '0';
	}
	else
	{
		for (i = 63; i >= 0; i--)
		{
			if (value & (1UL << i))
			{
				temp[pos++] = '1';
			}
			else if (pos > 0)
			{
				temp[pos++] = '0';
			}
		}
	}

	temp[pos] = '\0';
	for (i = 0; i < pos && *index < BUFFER_SIZE - 1; i++)
	{
		buffer[(*index)++] = temp[i];
	}
	buffer[*index] = '\0';
}
