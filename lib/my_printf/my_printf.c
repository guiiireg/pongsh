/**
 * ============================================================================
 *                              MY_PRINTF CORE
 * ============================================================================
 * File: my_printf.c
 * Description: Core implementation of my_printf with basic format specifiers.
 * Dependencies: my_printf.h
 * ============================================================================
 */

#include "../../include/my_printf.h"

/**
 * @brief Main printf implementation
 * @param format Format string with specifiers
 * @param ... Variable arguments
 * @return Number of characters printed
 */
int my_printf(const char *format, ...)
{
    va_list args;
    int count = 0;
    int i = 0;

    va_start(args, format);
    while (format[i]) {
        if (format[i] == '%') {
            i++;
            count += handle_format(format, args, &i);
        } else {
            my_putchar(format[i]);
            count++;
            i++;
        }
    }
    va_end(args);
    return count;
}
