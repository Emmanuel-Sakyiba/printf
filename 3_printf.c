#include <stdio.h>
#include <stdarg.h>
#include "main.h"

/**
 * print_number - Prints an integer to the standard output stream
 * @n: The integer to print
 *
 * Return: Number of characters printed
 */
int print_numbers(unsigned int n, int base, const char *digits)
{
	int printed_chars = 0;

	if (n / base != 0)
		printed_chars += print_numbers(n / base, base, digits);

	_putchar(digits[n % base]);
	printed_chars++;

	return (printed_chars);
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
	va_list args;
	unsigned int num;

	if (format == NULL)
		return (-1);

	va_start(args, format);

	for (i = 0; format[i] != '\0'; i++)
	{
		if (format[i] != '%')
		{
			printed_chars += _putchar(format[i]);
		}
		else
		{
			i++; /* Move past the '%' character */
			switch (format[i])
			{
			case 'u':
				{
					num = va_arg(args, unsigned int);
					printed_chars += print_numbers(num, 10, "0123456789");
				}
				break;
			case 'o':
				{
					num = va_arg(args, unsigned int);
					printed_chars += print_numbers(num, 8, "01234567");
				}
				break;
			case 'x':
				{
					num = va_arg(args, unsigned int);
					printed_chars += print_numbers(num, 16, "0123456789abcdef");
				}
				break;
			case 'X':
				{
					num = va_arg(args, unsigned int);
					printed_chars += print_numbers(num, 16, "0123456789ABCDEF");
				}
				break;
			default:
				break;
			}
		}
	}

	va_end(args);
	return (printed_chars);
}
