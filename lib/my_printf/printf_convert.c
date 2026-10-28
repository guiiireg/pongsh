#include "my.h"
#include "my_printf_internal.h"

/**
** @brief Runs the conversion matching a specifier.
**
** @param args The variadic arguments of my_printf.
** @param spec The conversion specifier.
**
** @return The number of bytes written, -1 on failure, or
**         PF_NOT_CONVERSION for an unsupported specifier.
*/
int pf_convert(va_list *args, char spec)
{
    if (spec == 'c') {
        return (pf_char(args));
    }
    if (spec == 's') {
        return (pf_string(args));
    }
    if (spec == 'd' || spec == 'i') {
        return (pf_signed(args));
    }
    if (spec == 'u') {
        return (pf_unsigned(args, "0123456789"));
    }
    if (spec == 'o') {
        return (pf_unsigned(args, "01234567"));
    }
    if (spec == 'x') {
        return (pf_unsigned(args, "0123456789abcdef"));
    }
    if (spec == 'X') {
        return (pf_unsigned(args, "0123456789ABCDEF"));
    }
    if (spec == 'p') {
        return (pf_pointer(args));
    }
    return (PF_NOT_CONVERSION);
}
