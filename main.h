#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdarg.h>

int _printf(const char *format, ...);

int handle_print(const char *format, int *index, va_list args, char *buffer);

void print_buffer(char buffer[], int *buff_ind);

int print_conversion(const char *format, int *index, va_list args);

int print_binary(unsigned int n);

int print_number(unsigned long int n, char *buffer, int *buff_ind, int base,
                 const char *digits);

int _puts(char c, char *buffer, int *buff_ind);

char *rot13(char *str);

int print_numbers(unsigned int n, int base, const char *digits);

int _putchar(char c);
int print_number2(int n);

int print_number1(unsigned int n, char *buffer, int *buff_ind, int base,
		 const char *digits);

int print_string(char *str, char *buffer, int *buff_ind);

int print_pointer(void *ptr, char *buffer, int *buff_ind);


#endif
