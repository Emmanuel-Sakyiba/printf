#include <stdio.h>
#include <stdargs.h>
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
	va_list value;
	va_start(value, format);
	int count = 0;
	char c;

	while (*format != '\0')
	{
		if (*format == '%')
		{
			format++;

			if (*format == '%') // handle doubele %%
			{
				putchar('%');
				count++;
			}
			else if (*format == 'c') //handle %c
			{
				char ch = va_arg(value, int);
				putchar(ch);
				count++;
			}
			else if (*format == 's') //handle %s
			{
				char *str = va_arg(value, char *);
				while (*str != '\0')
				{
					putchar(*str);
					count++;
					str++;
				}
			}
		}
		else
			putchar(*format);
		count++;

		format++;
	}
	va_end(value);
	return (count);
}

int main()
{
	char v = 'a';
	char str[] = "man";
	int y;

	y = _printf("the effah & Assibi team %c  %s\n", v, str);
	printf("the effah & Assibi team %c  %s\n", v, str);
	printf("count is: %d", y);

	return 0;

}
