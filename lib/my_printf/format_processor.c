// ============================
//       FORMAT_PROCESSOR
// ============================
// Made by Guireg on 17/08/2025
// Last update: 17/08/2025
// ============================
#include "../../include/my.h"

int process_format(char format, va_list args)
{
    if (format == 'c') {
        return handle_char(args);
    }
    if (format == 's') {
        return handle_string(args);
    }
    if (format == 'd' || format == 'i') {
        return handle_integer(args);
    }
    if (format == '%') {
        return handle_percent();
    }
    my_putchar('%');
    my_putchar(format);
    return 2;
}
