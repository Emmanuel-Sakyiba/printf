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
 * print_pointer - Prints a pointer to the buffer
 * @ptr: The pointer to print
 * @buffer: The buffer to store the pointer
 * @buff_ind: Index at which to add the pointer
 *
 * Return: Number of characters printed
 */
int print_pointer(void *ptr, char *buffer, int *buff_ind)
{
	unsigned long int address = (unsigned long int)ptr;
	int printed_chars = 0;

	printed_chars += _puts('0', buffer, buff_ind);
	printed_chars += _puts('x', buffer, buff_ind);
	printed_chars += print_number(address, buffer, buff_ind, 16, "0123456789abcdef");

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
	void *ptr;

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
			case 'p':
				/* Print a pointer */
				{
					ptr = va_arg(args, void *);
					printed_chars += print_pointer(ptr, buffer, &buff_ind);
				}
				break;
			default:
				/* Ignore unsupported conversion specifiers */
				break;
			}
		}
	}

	va_end(args);

	/* Print any remaining characters in the buffer */
	if (buff_ind > 0)
		write(1, buffer, buff_ind);

	return (printed_chars);
}

