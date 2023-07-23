#include <stdio.h>
#include <stdargs.h>
#include "main.h"
/**
 * _printf - prints
 * @format: the type of output
 *
 * Return: number of characters printed
*/
int _printf(const char *format, ...);
{
	va_lists args;
	char ch;
	int num_cp = 0;
	const char *str;

	va_start(format, args);

	while (*format != '\0')
	{
		if (*format == %)
		Format++;
		switch (*format)
		{
			case 'c';
			{
				ch = va_arg(arg, int);
				_putchar(ch);
				num_cp++;
			}
			Break;

			case 's';
			{
				*str = va_arg(args, const char);
				while (*str != '\0')
				{
					_putchar(*str);
					tr++;
					num_cp++;
				}
			}
			break;

			case '%';
				_putchar( % );
				num_cp++;
				break;
			default:

				break;
		}
	}

	else
	{
		_putchar(*format);
		num_cp++;
	}
	format++;

	va_end(args);

	return (num_cp);
}
