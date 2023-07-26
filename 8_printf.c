#include <stdio.h>
#include <unistd.h>
#include "main.h"
#include <stdarg.h>

#define BUFF_SIZE 1024

/**
 * _puts - ...
 * @str: ...
 * @buffer: ...
 * @buff_ind: ...
 *
 * Return: 0
 */
int _puts(char c, char *buffer, int *buff_ind)
{
	int i = 0;
	while (c[i] != '\0')
	{
		if (*buff_ind == BUFF_SIZE)
		{
			write(1, buffer, *buff_ind);
			*buff_ind = 0;
		}
		buffer[(*buff_ind)++] = c[i++];
	}
	return (i);
}

/**
 * _printf - ...
 * @format: ...
 *
 * Return: ...
 */
int _printf(const char *format, ...)
{
	int i, printed_chars = 0, buff_ind = 0;
	va_list args;
	char buffer[BUFF_SIZE];

	va_start(args, format);

	for (i = 0; format && format[i] != '\0'; i++)
	{
		if (format[i] != '%')
		{
			printed_chars += _puts(*format[i], buffer, &buff_ind);
			while (format[i] != '\0' && format[i] != '%')
				i++;
			i--;
		}
		else

	}

	write(1, buffer, buff_ind);
	va_end(args);

	return (printed_chars);
}
