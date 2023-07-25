#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>

int _printf(const char *format, ...);

int _putchar(char c);

void print_buffer(char buffer[], int *buff_ind);

char get_flags(const char *format, int *index);
int get_width(const char *format, int *index, va_list args);
int get_precision(const char *format, int *index, va_list args);
char get_size(const char *format, int *index);
int handle_print(const char *format, int *index, va_list args, char *buffer,
                 char flags, int width, int precision, char size);
int printf_bin(va_list val);

int handle_print(const char *format, int *index, va_list args, char *buffer);

void print_buffer(char buffer[], int *buff_ind);

#endif
