#include <stdio.h>
#include <stdarg.h>
#include "main.h"
#include "printf_helpers.h"
/**
 * print_buffer - Prints the contents of the buffer if it exists
 * @buffer: Array of chars
 * @buff_ind: Index at which to add next char, represents the length.
 */
void print_buffer(char buffer[], int *buff_ind)
{
	if (*buff_ind > 0)
	{
		write(1, &buffer[0], *buff_ind);
		*buff_ind = 0;
	}
}

/**
 * handle_print - Handles printing based on the conversion specifier
 * @format: Format string
 * @index: Pointer to the current position in the format string
 * @args: Variable arguments list
 * @buffer: Array to store characters before printing
 *
 * Return: Number of characters printed for the current conversion specifier
 */
int handle_print(const char *format, int *index, va_list args, char *buffer)
{
	int printed_chars = 0;
	int num = 0;
	int str_length, i;
	char int_str[12];

	if (format[*index] == 'd' || format[*index] == 'i')
	{
		num = va_arg(args, int);

		int_str[12]; /* Assuming a maximum of 12 digits for an int */
		str_length = snprintf(int_str, sizeof(int_str), "%d", num);

		for (i = 0; i < str_length; i++)
		{
			buffer[*index] = int_str[i];
			(*index)++;
			printed_chars++;
		}
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
	int i, printed_chars = 0, buff_ind = 0;
	va_list list;
	char buffer[BUFF_SIZE];

	if (format == NULL)
		return (-1);

	va_start(list, format);

	for (i = 0; format && format[i] != '\0'; i++)
	{
		if (format[i] != '%')
		{
			buffer[buff_ind++] = format[i];
			if (buff_ind == BUFF_SIZE)
				print_buffer(buffer, &buff_ind);
			printed_chars++;
		}
		else
		{
			print_buffer(buffer, &buff_ind);
			printed_chars += handle_print(format, &i, list, buffer);
		}
	}

	print_buffer(buffer, &buff_ind);

	va_end(list);

	return (printed_chars);
}
