#ifndef PRINTF_HELPERS_H
#define PRINTF_HELPERS_H

#include <stdarg.h>

/* Function prototypes for helper functions */
char get_flags(const char *format, int *index);
int get_width(const char *format, int *index, va_list args);
int get_precision(const char *format, int *index, va_list args);
char get_size(const char *format, int *index);
int handle_print(const char *format, int *index, va_list args, char *buffer,
                 char flags, int width, int precision, char size);

#endif /* PRINTF_HELPERS_H */
