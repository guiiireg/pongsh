/**
 * ============================================================================
 *                              MY_PRINTF HEADER
 * ============================================================================
 * File: my_printf.h
 * Description: Header file for the my_printf implementation with basic format
 *              specifiers (%s, %c, %d, %%).
 * Dependencies: stdarg.h
 * ============================================================================
 */

#ifndef MY_PRINTF_H
    #define MY_PRINTF_H

    #include <stdarg.h>
    #include "pongsh.h"

// ---- Function prototypes ----
int my_printf(const char *format, ...);
int handle_format(const char *format, va_list args, int *i);
int handle_string(va_list args);
int handle_char(va_list args);
int handle_int(va_list args);
int handle_percent(void);
int handle_default(const char *format, int *i);

#endif /* MY_PRINTF_H */
