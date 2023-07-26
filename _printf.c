#include <stdio.h>
#include <stdarg.h>
#include "main.h"

/**
 * print_conversion - Prints a conversion specifier and its argument
 * @format: Format string
 * @index: Pointer to the current position in the format string
 * @args: Variable arguments list
 *
 * Return: Number of characters printed for the current conversion specifier
 */
int print_conversion(const char *format, int *index, va_list args)
{
	int printed_chars = 0;
	char c, *str;

	(*index)++; /* Skip the '%' character */
	switch (format[*index])
	{
	case 'c':
	{
		c = va_arg(args, int);
		printed_chars += _putchar(c);
	}
	break;
	case 's':
	{	
		str = va_arg(args, char *);
		if (str == NULL)
			str = "(null)";
		while (*str)
		{
			printed_chars += _putchar(*str);
			str++;
		}
	}
	break;
	case '%':
	{
		/* Print the '%' character itself */
		printed_chars += _putchar('%');
	}
	break;
	default:
		/* Ignore unsupported conversion specifiers */
		break;
	}

	return printed_chars;
}

/**
 * _printf - Printf function
 * @format: Format string
 *
 * Return: Number of characters printed
 */
int _printf(const char *format, ...)
{
	int i, printed_chars = 0;
	va_list list;

	if (format == NULL)
		return (-1);

	va_start(list, format);

	for (i = 0; format && format[i] != '\0'; i++)
	{
		if (format[i] != '%')
		{
			printed_chars += _putchar(format[i]);
		}
		else
		{
			printed_chars += print_conversion(format, &i, list);
		}
	}

	va_end(list);

	return (printed_chars);
}
