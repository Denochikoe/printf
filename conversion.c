#include "main.h"

void convert_char(char value, char *buffer, int *index)
{
	buffer[(*index)++] = value;
}

void convert_string(const char *value, char *buffer, int *index)
{
	while (*value)
	{
		buffer[(*index)++] = *value++;
	}
}

void convert_int(int value, int flags, int width, int precision, char *buffer, int *index)
{
	char temp[64];
	int len;
	int i;

	len = snprintf(temp, sizeof(temp), "%*.*d", width, precision, value);

	if (flags & FLAG_PLUS && value >= 0)
	{
		buffer[(*index)++] = '+';
	}
	if (flags & FLAG_SPACE && value >= 0)
	{
		buffer[(*index)++] = ' ';
	}

	for (i = 0; i < len; i++)
	{
		buffer[(*index)++] = temp[i];
	}
}

void convert_unsigned(unsigned int value, int base, int flags, int width, int precision, char *buffer, int *index)
{
	char temp[BUFFER_SIZE];
	char digits[] = "0123456789abcdef";
	char digits_upper[] = "0123456789ABCDEF";
	int i = 0;
	unsigned int num = value;

	char *digits_to_use = (base == 16 && (flags & FLAG_UPPER)) ? digits_upper : digits;

	do {
		temp[i++] = digits_to_use[num % base];
		num /= base;
	} while (num > 0);

	while (i < precision)
	{
		temp[i++] = '0';
	}

	if (flags & FLAG_ZERO)
	{
		while (i < width)
		{
			temp[i++] = '0';
		}
	}
	else
	{
		while (i < width)
		{
			temp[i++] = ' ';
		}
	}

	while (i > 0)
	{
		buffer[(*index)++] = temp[--i];
	}
}

void convert_binary(unsigned int value, char *buffer, int *index)
{
	char temp[33];
	int pos = 0;
	int i;

	if (value == 0)
	{
		temp[pos++] = '0';
	}
	else
	{
		for (i = 31; i >= 0; i--)
		{
			if (value & (1 << i))
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
	for (i = 0; i < pos; i++)
	{
		buffer[(*index)++] = temp[i];
	}
}
