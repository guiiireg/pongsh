// ============================
//           MY_PRINTF
// ============================
// Made by Guireg on 17/08/2025
// Last update: 17/08/2025
// ============================
#include "../../include/my.h"

int my_printf(char const *format, ...)
{
    va_list args;
    int i = 0;
    int count = 0;

    va_start(args, format);
    while (format[i] != '\0') {
        if (format[i] == '%' && format[i + 1] != '\0') {
            i++;
            count += process_format(format[i], args);
        } else {
            my_putchar(format[i]);
            count++;
        }
        i++;
    }
    va_end(args);
    return count;
}
