#include <stdio.h>
#include <stdarg.h>
#include "main.h"

/**
 * _printf - prints
 * @format: a pointer to format
 *
 * Return: printf char
 */
int _printf(const char *format, ...)
{
	va_list args;
	char ch;
	const char *str;

	int num_chars_printed = 0;

	va_start(args, format);

	while (*format != '\0')
	{
		if (*format == '%')
		{
			format++;
			switch (*format)
			{
				case 'c':
					{
						ch = (char)va_arg(args, int);
						putchar(ch);
						num_chars_printed++;
					}
					break;
				case 's':
					{
						str = va_arg(args, const char *);
						while (*str != '\0')
						{
							putchar(*str);
							str++;
							num_chars_printed++;
						}
					}
					break;
				case '%':
					putchar('%');
					num_chars_printed++;
					break;
				default:
					break;
			}
		}
		else
		{
			putchar(*format);
			num_chars_printed++;
		}

<<<<<<< HEAD
		format++;
	}

	va_end(args);
	return (num_chars_printed);
=======
			while (*str != '\0')
			{
				putchar(*str);
				count++;
				str++;
			}
		}

		else
			putchar(*format);
		format++;
		count++;
	}
	{

		va_end(args);
		return (count);

	}
>>>>>>> bdfcaafd23397861570825d1289e38bc9719ebf3
}
