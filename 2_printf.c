#include <stdio.h>
#include <stdarg.h>
#include "main.h"

/**
 * print_number - Prints an integer to the standard output stream
 * @n: The integer to print
 *
 * Return: Number of characters printed
 */
int print_number2(int n)
{
	unsigned int num;
	int printed_chars = 0;

	if (n < 0)
	{
		printed_chars += _putchar('-');
		num = -n;
	}
	else
		num = n;

	if (num / 10 != 0)
		printed_chars += print_number2(num / 10);

	printed_chars += _putchar(num % 10 + '0');

	return (printed_chars);
}

/**
 * print_binary - Prints an unsigned integer in binary format
 * @n: The unsigned integer to print as binary
 *
 * Return: Number of characters printed
 */
int print_binary(unsigned int n)
{
	int printed_chars = 0;
	unsigned int mask = 1;
	int bits = sizeof(n) * 8;

	while (bits--)
	{
		printed_chars += _putchar((n & mask) ? '1' : '0');
		mask <<= 1;
	}

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
	int num;
	unsigned int nums;

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
			if (format[i] == 'd' || format[i] == 'i')
			{
				/* Print a signed decimal integer */
				num = va_arg(args, int);
				printed_chars += print_number2(num);
			}
			else if (format[i] == 'b')
			{
				/* Print an unsigned int as binary */
				nums = va_arg(args, unsigned int);
				printed_chars += print_binary(nums);
			}
		}
	}

	va_end(args);

	return (printed_chars);
}

