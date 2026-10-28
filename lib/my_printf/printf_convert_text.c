#include <stddef.h>

#include "my.h"
#include "my_printf_internal.h"

/**
** @brief Writes a %c conversion: one character.
**
** The int argument is converted to an unsigned char.
**
** @param args The variadic arguments of my_printf.
**
** @return The number of bytes written, or -1 on failure.
*/
int pf_char(va_list *args)
{
    int value = va_arg(*args, int);

    return (my_putchar((char)value));
}

/**
** @brief Writes a %s conversion: a string.
**
** A NULL argument is printed as (null), like glibc does.
**
** @param args The variadic arguments of my_printf.
**
** @return The number of bytes written, or -1 on failure.
*/
int pf_string(va_list *args)
{
    char const *str = va_arg(*args, char const *);

    if (str == NULL) {
        str = "(null)";
    }
    return (my_putstr(str));
}
