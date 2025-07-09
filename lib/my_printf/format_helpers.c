/**
 * ============================================================================
 *                              FORMAT HELPERS
 * ============================================================================
 * File: format_helpers.c
 * Description: Helper functions for format specifiers in my_printf.
 * Dependencies: my_printf.h
 * ============================================================================
 */

#include "../../include/my_printf.h"

int handle_string(va_list args)
{
    char *str = va_arg(args, char *);

    if (!str)
        str = "(null)";
    return my_putstr(str);
}

int handle_char(va_list args)
{
    my_putchar(va_arg(args, int));
    return 1;
}

int handle_int(va_list args)
{
    return my_putnbr(va_arg(args, int));
}

int handle_percent(void)
{
    my_putchar('%');
    return 1;
}

int handle_default(const char *format, int *i)
{
    my_putchar('%');
    my_putchar(format[*i]);
    return 2;
}
