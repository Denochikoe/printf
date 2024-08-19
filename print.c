#include "main.h"

/**
 * _printf - Custom implementation of printf function
 * @format: Format string containing the desired text and
 * specifiers
 *
 * Return: Total length of the output string
 */

int _printf(const char *format, ...)
{
	char buffer[BUFFER_SIZE];
	int index = 0;
	va_list args;
	const char *p;
	int flags, width, precision, length;
	int total_length = 0;
	const char *str;

	va_start(args, format);

	for (p = format; *p; p++)
	{
		if (*p == '%')
		{
			p++;
			if (*p == 'S')
			{
				str = va_arg(args, const char *);
				convert_string(str, buffer, &index);
			}
			else if (*p == '%')
			{
				buffer[index++] = '%';
			}
			else
			{
				flags = 0;
				width = 0;
				precision = -1;
				length = 0;

				handle_flags(&p, &flags);
				handle_width(&p, &width);
				handle_precision(&p, &precision);
				handle_length_modifier(&p, &length);

				switch (*p)
				{
					case 'c':
						convert_char(va_arg(args, int), buffer, &index);
						break;
					case 's':
						convert_string(va_arg(args, char*), buffer, &index);
						break;
					case 'd':
					case 'i':
						convert_int(va_arg(args, int), flags, width, precision, buffer, &index);
						break;
					case 'u':
						convert_unsigned(va_arg(args, unsigned int), 10, flags, width, precision, buffer, &index);
						break;
					case 'o':
						convert_unsigned(va_arg(args, unsigned int), 8, flags, width, precision, buffer, &index);
						break;
					case 'x':
						convert_unsigned(va_arg(args, unsigned int), 16, flags, width, precision, buffer, &index);
						break;
					case 'X':
						convert_unsigned(va_arg(args, unsigned int), 16, flags | FLAG_UPPER, width, precision, buffer, &index);
						break;
					case 'p':
						convert_pointer(va_arg(args, void*), buffer, &index);
						break;
					case 'b':
						convert_binary(va_arg(args, unsigned int), buffer, &index);
						break;
					case 'S':
						convert_string(va_arg(args, char*), buffer, &index);
						break;
					case 'r':
						convert_reversed_string(va_arg(args, char*), buffer, &index);
						break;
					case 'R':
						convert_rot13_string(va_arg(args, char*), buffer, &index);
						break;
					case '\\':
						if (*(p + 1) == 'x')
						{
							handle_nonprintable((char)va_arg(args, int), buffer, &index);
							p++;
						}
						break;
					default:
						buffer[index++] = '%';
						buffer[index++] = *p;
						break;
				}
			}
		}
		else
		{
			buffer[index++] = *p;
		}

		if (index >= BUFFER_SIZE - 1)
			break;
	}

	buffer[index] = '\0';
	va_end(args);
	total_length = index;

	write(STDOUT_FILENO, buffer, index);

	return total_length;
}
