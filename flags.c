#include "main.h"

void handle_flags(const char **format, int *flags)
{
	*flags = 0;

	while (**format == '+' || **format == ' ' || **format == '#' || **format == '-')
	{
		switch (**format) {
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

void handle_width(const char **format, int *width)
{
	*width = 0;

	if (isdigit(**format))
	{
		*width = strtol(*format, (char **)format, 10);
	}
}


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

void handle_length_modifier(const char **format, int *length)
{
	*length = 0;

	switch (**format) {
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
