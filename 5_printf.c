#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>
#include "main.h"

/**
 * _putchar - Prints a character to the buffer
 * @c: The character to print
 * @buffer: The buffer to store the character
 * @buff_ind: Index at which to add the character
 *
 * Return: On success, the character is returned.
 *         On error, -1 is returned.
 */
int _puts(char c, char *buffer, int *buff_ind)
{
	if (*buff_ind >= 1024)
	{
		write(1, buffer, *buff_ind);
		*buff_ind = 0;
	}
	buffer[*buff_ind] = c;
	(*buff_ind)++;
	return (1);
}

/**
 * print_number - Prints an integer to the buffer
 * @n: The integer to print
 * @buffer: The buffer to store the integer
 * @buff_ind: Index at which to add the integer
 * @base: The base for conversion
 * @digits: The digits for the base
 *
 * Return: Number of characters printed
 */
int print_number1(unsigned int n, char *buffer, int *buff_ind, int base,
		 const char *digits)
{
	int printed_chars = 0;

	if (n / base != 0)
		printed_chars += print_number1(n / base, buffer, buff_ind, base, digits);

	printed_chars += _puts(digits[n % base], buffer, buff_ind);

	return (printed_chars);
}

/**
 * print_string - Prints a string to the buffer
 * @str: The string to print
 * @buffer: The buffer to store the string
 * @buff_ind: Index at which to add the string
 *
 * Return: Number of characters printed
 */
int print_string(char *str, char *buffer, int *buff_ind)
{
	int i, printed_chars = 0;
	unsigned char ch;

	if (str == NULL)
		str = "(null)";

	for (i = 0; str[i] != '\0'; i++)
	{
		ch = str[i];
		if (ch < 32 || ch >= 127)
		{
			/* Print non-printable characters as \x followed by the ASCII code value in hexadecimal */
			printed_chars += _puts('\\', buffer, buff_ind);
			printed_chars += _puts('x', buffer, buff_ind);
			printed_chars += print_number1(ch, buffer, buff_ind, 16, "0123456789ABCDEF");
		}
		else
		{
			/* Print printable characters normally */
			printed_chars += _puts(ch, buffer, buff_ind);
		}
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
	int i, printed_chars = 0, buff_ind = 0;
	va_list args;
	char buffer[1024];
	char *str;

	if (format == NULL)
		return (-1);

	va_start(args, format);

	for (i = 0; format[i] != '\0'; i++)
	{
		if (format[i] != '%')
		{
			printed_chars += _puts(format[i], buffer, &buff_ind);
		}
		else
		{
			i++; /* Move past the '%' character */
			switch (format[i])
			{
			case 'S':
				{
					str = va_arg(args, char *);
					printed_chars += print_string(str, buffer, &buff_ind);
				}
				break;
			default:
				break;
			}
		}
	}

	va_end(args);

	if (buff_ind > 0)
		write(1, buffer, buff_ind);

	return (printed_chars);
}

