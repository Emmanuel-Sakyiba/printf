#include <stdio.h>
#include <stdarg.h>
#include "main.h"
#include <unistd.h>

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
int print_number(unsigned long int n, char *buffer, int *buff_ind, int base,
		const char *digits)
{
	int printed_chars = 0;

	if (n / base != 0)
		printed_chars += print_number(n / base, buffer, buff_ind, base, digits);

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
			printed_chars += print_number(ch, buffer, buff_ind, 16, "0123456789ABCDEF");
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
	int i, width = 0, precision = -1, printed_chars = 0, buff_ind = 0, zero_flag = 0;
	va_list args;
	char buffer[1024];

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

			/* Handle flag characters '+', ' ', '#', '0', and '-' if they appear before the conversion specifier */
			while (format[i] == ' ' || format[i] == '+' || format[i] == '#' || format[i] == '0' || format[i] == '-')
			{
				if (format[i] == '-')
					width = -1;
				if (format[i] == '0')
					zero_flag = 1;
				i++;
			}

			/* Handle field width */
			while (format[i] >= '0' && format[i] <= '9')
			{
				if (width >= 0)
					width = width * 10 + (format[i] - '0');
				else
					precision = precision * 10 + (format[i] - '0');
				i++;
			}

			if (width < 0)
			{
				width = -width;
				/* Left align with '-' flag */
			}

			if (format[i] == '.')
			{
				i++; /* Move past the '.' character */
				precision = 0;
				while (format[i] >= '0' && format[i] <= '9')
				{
					precision = precision * 10 + (format[i] - '0');
					i++;
				}
			}

			switch (format[i])
			{
				case 'c':
					/* Print a character */
					{
						char ch = va_arg(args, int);
						printed_chars += _puts(ch, buffer, &buff_ind);
					}
					break;
				case 's':
					/* Print a string */
					{
						char *str = va_arg(args, char *);
						int len = 0;
						if (str == NULL)
							str = "(null)";
						while (str[len] != '\0')
							len++;
						if (precision >= 0 && precision < len)
							len = precision;
						if (width > len)
						{
							int spaces = width - len;
							while (spaces--)
								printed_chars += _puts(' ', buffer, &buff_ind);
						}
						printed_chars += print_string(str, buffer, &buff_ind);
					}
					break;
				case '%':
					/* Print the '%' character */
					printed_chars += _puts('%', buffer, &buff_ind);
					break;
				case 'd':
				case 'i':
					/* Print a signed integer */
					{
						long int num = va_arg(args, int);
						int len = 0, num_copy = num;
						while (num_copy != 0)
						{
							len++;
							num_copy /= 10;
						}
						if (num < 0)
							len++; /* Account for the negative sign */
						if (precision >= 0 && precision > len)
							precision = precision - len;
						else
							precision = 0;
						if (zero_flag)
						{
							printed_chars += _puts((num < 0) ? '-' : '+', buffer, &buff_ind);
							zero_flag = 0;
						}
						if (width > len + precision)
						{
							int spaces = width - (len + precision);
							while (spaces--)
								printed_chars += _puts(' ', buffer, &buff_ind);
						}
						if (num < 0)
						{
							num = -num;
							printed_chars += _puts('-', buffer, &buff_ind);
						}
						while (precision--)
							printed_chars += _puts('0', buffer, &buff_ind);
						printed_chars += print_number(num, buffer, &buff_ind, 10, "0123456789");
					}
					break;
				case 'u':
					/* Print an unsigned integer */
					{
						unsigned long int num = va_arg(args, unsigned int);
						int len = 0, num_copy = num;
						while (num_copy != 0)
						{
							len++;
							num_copy /= 10;
						}
						if (precision >= 0 && precision > len)
							precision = precision - len;
						else
							precision = 0;
						if (zero_flag)
						{
							printed_chars += _puts('+', buffer, &buff_ind);
							zero_flag = 0;
						}
						if (width > len + precision)
						{
							int spaces = width - (len + precision);
							while (spaces--)
								printed_chars += _puts(' ', buffer, &buff_ind);
						}
						while (precision--)
							printed_chars += _puts('0', buffer, &buff_ind);
						printed_chars += print_number(num, buffer, &buff_ind, 10, "0123456789");
					}
					break;
				case 'o':
					/* Print an octal number */
					{
						unsigned long int num = va_arg(args, unsigned int);
						int len = 0, num_copy = num;
						while (num_copy != 0)
						{
							len++;
							num_copy /= 8;
						}
						if (precision >= 0 && precision > len)
							precision = precision - len;
						else
							precision = 0;
						if (zero_flag)
						{
							printed_chars += _puts('+', buffer, &buff_ind);
							zero_flag = 0;
						}
						if (width > len + precision)
						{
							int spaces = width - (len + precision);
							while (spaces--)
								printed_chars += _puts(' ', buffer, &buff_ind);
						}
						while (precision--)
							printed_chars += _puts('0', buffer, &buff_ind);
						printed_chars += print_number(num, buffer, &buff_ind, 8, "01234567");
					}
					break;
				case 'x':
					/* Print a lowercase hexadecimal number */
					{
						unsigned long int num = va_arg(args, unsigned int);
						int len = 0, num_copy = num;
						while (num_copy != 0)
						{
							len++;
							num_copy /= 16;
						}
						if (precision >= 0 && precision > len)
							precision = precision - len;
						else
							precision = 0;
						if (zero_flag)
						{
							printed_chars += _puts('+', buffer, &buff_ind);
							zero_flag = 0;
						}
						if (width > len + precision)
						{
							int spaces = width - (len + precision);
							while (spaces--)
								printed_chars += _puts(' ', buffer, &buff_ind);
						}
						while (precision--)
							printed_chars += _puts('0', buffer, &buff_ind);
						printed_chars += print_number(num, buffer, &buff_ind, 16, "0123456789abcdef");
					}
					break;
				case 'X':
					/* Print an uppercase hexadecimal number */
					{
						unsigned long int num = va_arg(args, unsigned int);
						int len = 0, num_copy = num;
						while (num_copy != 0)
						{
							len++;
							num_copy /= 16;
						}
						if (precision >= 0 && precision > len)
							precision = precision - len;
						else
							precision = 0;
						if (zero_flag)
						{
							printed_chars += _puts('+', buffer, &buff_ind);
							zero_flag = 0;
						}
						if (width > len + precision)
						{
							int spaces = width - (len + precision);
							while (spaces--)
								printed_chars += _puts(' ', buffer, &buff_ind);
						}
						while (precision--)
							printed_chars += _puts('0', buffer, &buff_ind);
						printed_chars += print_number(num, buffer, &buff_ind, 16, "0123456789ABCDEF");
					}
					break;
				case 'p':
					/* Print a pointer address */
					{
						void *ptr = va_arg(args, void *);
						unsigned long int address = (unsigned long int)ptr;
						printed_chars += _puts('0', buffer, &buff_ind);
						printed_chars += _puts('x', buffer, &buff_ind);
						printed_chars += print_number(address, buffer, &buff_ind, 16, "0123456789abcdef");
					}
					break;
			}
		}
	}

	/* Flush the buffer */
	write(1, buffer, buff_ind);

	va_end(args);

	return (printed_chars);
}

