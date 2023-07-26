#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include "main.h"

/**
 * _putchar - Writes a character to the buffer
 * @c: The character to write
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

    if (str == NULL)
        str = "(null)";

    for (i = 0; str[i] != '\0'; i++)
    {
        printed_chars += _puts(str[i], buffer, buff_ind);
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

            if (format[i] == 'r')
            {
                /* Print a reversed string */
                char *str = va_arg(args, char *);
                int len = 0;
                if (str == NULL)
                    str = "(null)";
                while (str[len] != '\0')
                    len++;
                for (len--; len >= 0; len--)
                    printed_chars += _puts(str[len], buffer, &buff_ind);
            }
            else if (format[i] == 'c')
            {
                /* Print a character */
                char ch = va_arg(args, int);
                printed_chars += _puts(ch, buffer, &buff_ind);
            }
            else if (format[i] == 's')
            {
                /* Print a string */
                char *str = va_arg(args, char *);
                printed_chars += print_string(str, buffer, &buff_ind);
            }
            else if (format[i] == '%')
            {
                /* Print the '%' character */
                printed_chars += _puts('%', buffer, &buff_ind);
            }
            else
            {
                /* Invalid format specifier, just print the '%' and the next character */
                printed_chars += _puts('%', buffer, &buff_ind);
                printed_chars += _puts(format[i], buffer, &buff_ind);
            }
        }
    }

    /* Flush the buffer */
    write(1, buffer, buff_ind);

    va_end(args);

    return (printed_chars);
}

