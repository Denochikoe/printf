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
    int total_length = 0;

    va_start(args, format);

    for (p = format; *p; p++)
    {
        if (*p == '%')
        {
            p++;
            process_specifier(p, args, buffer, &index);
        }
        else
        {
            buffer[index++] = *p;
        }

        if (index >= BUFFER_SIZE - 1)
	{
            write(STDOUT_FILENO, buffer, index);
	    total_length += index;
	    index = 0;
	}
    }

    if (index > 0)
    {
	    write(STDOUT_FILENO, buffer, index);
	    total_length += index;
    }
    va_end(args);

    return total_length;
}

/**
 * process_specifier - Handles the format specifiers
 * @p: Pointer to the current character in the format string
 * @args: Variable argument list
 * @buffer: Buffer to store the output
 * @index: Index for the buffer
 */
void process_specifier(const char *p, va_list args, char *buffer, int *index)
{
    int flags = 0, width = 0, precision = -1, length = 0;

    process_format_specifiers(&p, &flags, &width, &precision
	, &length);

    if (*p == 'c' || *p == 's' || *p == 'd' || *p == 'u' || 
		    *p == 'o' || *p == 'x' || *p == 'X' || 
		    *p == 'p')
    {
	    handle_common_specifiers(p, args, buffer, index
			    , flags, width, precision);
    }
    else if (*p == 'b' || *p == 'S' || *p == 'r' || *p == 'R')
    {
	    handle_custom_specifiers(p, args, buffer, index);
    }
    else if (*p == '%')
    {
	    buffer[(*index)++] = '%';
    }
    else if (*p == '\\')
    {
	    handle_escape_sequence(&p, args, buffer, index);
    }
    else
    {
	    handle_unknown_specifier(p, buffer, index);
    }
}

int get_base(char specifier)
{
    if (specifier == 'o') return 8;
    if (specifier == 'x' || specifier == 'X') return 16;
    return 10;
}
