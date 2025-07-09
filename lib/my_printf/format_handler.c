/**
 * ============================================================================
 *                              FORMAT HANDLER
 * ============================================================================
 * File: format_handler.c
 * Description: Handles format specifiers for my_printf (%s, %c, %d, %%).
 * Dependencies: my_printf.h
 * ============================================================================
 */

#include "../../include/my_printf.h"

/**
 * @brief Handles format specifiers
 * @param format Format string
 * @param args Variable arguments list
 * @param i Pointer to current position in format string
 * @return Number of characters printed
 */
static int execute_format_handler(char specifier, va_list args,
    const char *format, int *i)
{
    if (specifier == 's') {
        return handle_string(args);
    }
    if (specifier == 'c') {
        return handle_char(args);
    }
    if (specifier == 'd') {
        return handle_int(args);
    }
    if (specifier == '%') {
        return handle_percent();
    }
    return handle_default(format, i);
}

int handle_format(const char *format, va_list args, int *i)
{
    int count = execute_format_handler(format[*i], args, format, i);

    (*i)++;
    return count;
}
