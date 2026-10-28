#ifndef MY_PRINTF_INTERNAL_H_
# define MY_PRINTF_INTERNAL_H_

#include <stdarg.h>

/*
** Internal helpers of my_printf.
**
** These functions are shared between the my_printf source files and
** are not part of the public libmy API. Their names are prefixed with
** pf_ to avoid polluting the library namespace.
**
** Each writing helper returns the number of bytes written, or -1 on
** failure, and advances the format index past what it consumed.
*/

/* Returned by pf_convert when the specifier is not a conversion. */
# define PF_NOT_CONVERSION (-2)

int pf_plain(char const *format, int *index);
int pf_percent(va_list *args, char const *format, int *index);
int pf_directive(va_list *args, char const *format, int *index);
int pf_format(va_list *args, char const *format);

int pf_char(va_list *args);
int pf_string(va_list *args);
int pf_base(unsigned long value, char const *base);
int pf_signed(va_list *args);
int pf_unsigned(va_list *args, char const *base);
int pf_pointer(va_list *args);
int pf_convert(va_list *args, char spec);

#endif // MY_PRINTF_INTERNAL_H_
