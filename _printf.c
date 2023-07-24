#include <stdio.h>
#include <stdarg.h>
#include "main.h"

int _printf(const char *format, ...);

/**
 * _printf - a function that produces output according to a format
 * @format: the type of output
 * A project performed by Emmanuel Effah and Benjamin Assibi
 *
 * Return: number of characters printed
 */
int _printf(const char *format, ...)
{
	int count = 0;

	va_list args;

	va_start(args, format);

	while (*format != '\0')
	{

		if (*format == '%')
		{
			putchar('%');
			format++;
		}
		else if (*format == 'c')
		{
			char ch = va_arg(args, int);

			putchar(ch);
			count++;
		}
		else if (*format == 's')
		{
			char *str = va_arg(args, char *);

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
}
