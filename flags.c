#include "main.h"

/**
 * handle_flags - Parses and sets the flags for the format
 * specifiers.
 * @format: Pointer to the format string (updated as flags are
 * parsed).
 * @flags: Pointer to an integer that will store the parsed
 * flags.
 *
 * Description: This function checks the format string for
 * flags such as '+', ' ', '#', '0', and '-' and sets the
 * corresponding bits in the integer pointed to by 'flags'.
 *  The format string pointer is incremented as flags are
 *  parsed.
 *
 * Return: void
 */
void handle_flags(const char **format, int *flags)
{
	*flags = 0;

	while (**format == '+' || **format == ' '
		 || **format == '#' || **format == '-'
		 || **format == '0')
	{
		switch (**format)
		{
		case '+':
			*flags |= FLAG_PLUS;
			break;
		case ' ':
			*flags |= FLAG_SPACE;
			break;
		case '#':
			*flags |= FLAG_HASH;
			break;
		case '0':
			*flags |= FLAG_ZERO;
			break;
		case '-':
			*flags |= FLAG_MINUS;
			break;
		}
		(*format)++;
	}
}

/**
 * handle_width - Parses and sets the width for the format
 * specifier.
 * @format: Pointer to the format string (updated as width
 * is parsed).
 * @width: Pointer to an integer that will store the parsed
 * width.
 *
 * Description: This function checks if the format string
 * contains a width specification. If a width is specified,
 * it is parsed and stored in the integer pointed to by 'width'
 * . The format string pointer is incremented as the width is
 * parsed.
 *
 * Return: void
 */
void handle_width(const char **format, int *width)
{
	*width = 0;

	if (isdigit(**format))
	{
		*width = strtol(*format, (char **)format, 10);
	}
}

/**
 * handle_precision - Parses and sets the precision for the
 * format specifier.
 * @format: Pointer to the format string (update as precision
 * is parsed).
 * @precision: Pointer to an integer that will store the parsed
 * precision.
 *
 * Description: This function checks if the format string
 * contains a precision specification (indicated by a dot '.').
 * if a precision is specified, it is parsed and stored in the
 * integer pointed to by 'precision'. The format string pointer
 * is incremented as the precision is parsed. If no precision
 * is specified, the precision is set to -1.
 */
void handle_precision(const char **format, int *precision)
{
	*precision = -1;

	if (**format == '.')
	{
		(*format)++;
		if (isdigit(**format))
		{
			*precision = strtol(*format, (char **)format, 10);
		}
	}
}

/**
 * handle_length_modifier - Parses and sets the length modifier
 * for the format specifier.
 * @format: Pointer to the format string (updated as length
 * modifier is parsed).
 * @length: Pointer to an integer that will store the parsed
 * length modifier.
 *
 * Description: This function checks if the format string
 * contains a length modifier (such as 'I', 'II', 'h', or 'hh').
 * If a length modifier is found, it is parsed and stored in the
 * integer pointed to by 'length'. The format string pointer
 * is incremented as the length modifier is parsed.
 * If no length modifier is specified, the length is set to 0.
 *
 * Return: void
 */
void handle_length_modifier(const char **format, int *length)
{
	*length = 0;

	switch (**format)
	{
	case 'l':
		*length = LENGTH_LONG;
		(*format)++;
		if (**format == 'l')
		{
			*length = LENGTH_LONG_LONG;
			(*format)++;
		}
		break;
	case 'h':
		*length = LENGTH_SHORT;
		(*format)++;
		if (**format == 'h')
		{
			*length = LENGTH_CHAR;
			(*format)++;
		}
		break;
	default:
		break;
	}
}
