#include "my.h"
#include "my_printf_internal.h"

/**
** @brief Writes a %p conversion: a pointer as hexadecimal.
**
** The output is prefixed with 0x. A NULL pointer prints 0x0.
**
** @param args The variadic arguments of my_printf.
**
** @return The number of bytes written, or -1 on failure.
*/
int pf_pointer(va_list *args)
{
    unsigned long value = (unsigned long)va_arg(*args, void *);
    int status = my_putstr("0x");

    if (status == -1) {
        return (-1);
    }
    status = pf_base(value, "0123456789abcdef");
    if (status == -1) {
        return (-1);
    }
    return (status + 2);
}
