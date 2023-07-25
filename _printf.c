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
						_putchar(ch);
						num_chars_printed++;
					}
					break;
				case 's':
					{
						str = va_arg(args, const char *);
						while (*str != '\0')
						{
							_putchar(*str);
							str++;
							num_chars_printed++;
						}
					}
					break;
				case '%':
					_putchar('%');
					num_chars_printed++;
					break;
				case 'r';
					_putchar('%');
					num_chars_printed++;
					break;
				default:
					break;
			}
		}
		else
		{
			_putchar(*format);
			num_chars_printed++;
		}

		format++;
	}

	va_end(args);
	return (num_chars_printed);
}
