#include "main.h"

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
