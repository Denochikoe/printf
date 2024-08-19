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

/**
 * convert_reversed_string - Reverses a string and stores it in
 * the buffer.
 * @value: The string to be reversed.
 * @buffer: The buffer to store the reversed string.
 * @index: Pointer to the current index in the buffer.
 *
 * Description: This function takes a string, reverses it, and
 * stores the reversed string in the buffer. If the input
 * string is NULL, the function stores the string "(null)"
 * in the buffer.
 *
 * Return: void
 */
void convert_reversed_string(const char *value, char *buffer, int *index)
{
	int i;
	int len;
	const char *null_str;

	if (value == NULL)
	{
		null_str = "(null)";
		while (*null_str)
		{
			buffer[(*index)++] = *null_str++;
		}
		return;
	}

	len = strlen(value);
	for (i = len - 1; i >= 0; i--)
	{
		buffer[(*index)++] = value[i];
	}
}

/**
 * convert_rot13_string - Converts a string to ROT13 and stores
 * it in the buffer.
 * @value: The string to be converted to ROT13.
 * @buffer: The buffer to store the converted string.
 * @index: Pointer to the current index in the buffer.
 *
 * Description: This function takes a string, applies ROT13
 * encoding to it, and stores the encoded string in the buffer.
 * If the character is not an alphabetic character, it is
 * copied as-is to the buffer.
 *
 * Return: void
 */
void convert_rot13_string(const char *value, char *buffer, int *index)
{
	char c;

	while (*value)
	{
		c = *value++;

		if (isalpha(c))
		{
			if (isupper(c))
			{
				buffer[(*index)++] = ((c - 'A' + 13) % 26) + 'A';
			}
			else
			{
				buffer[(*index)++] = ((c - 'a' + + 13) % 26) + 'a';
			}
		} else
		{
			buffer[(*index)++] = c;
		}
	}
}

/**
 * convert_pointer - Converts a pointer to a string and stores
 * it in the buffer.
 * @value: The pointer to be converted.
 * @buffer: The buffer to store the converted pointer string.
 * @index: Pointer to the current index in the buffer.
 *
 * Return: void
 * Description: This function converts a pointer to a string
 * representation (using the %p format) and stores the result
 * in the provided buffer.
 */
void convert_pointer(void *value, char *buffer, int *index)
{
	char temp[64];
	int i;

	snprintf(temp, sizeof(temp), "%p", value);

	for (i = 0; temp[i] != '\0'; i++)
	{
		buffer[(*index)++] = temp[i];
	}
}
