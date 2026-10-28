#include "my.h"
#include "my_printf_internal.h"

/**
** @brief Writes an unsigned value in the given base.
**
** @param value The value to write.
** @param base The digits of the base, in order.
**
** @return The number of bytes written, or -1 on failure.
*/
int pf_base(unsigned long value, char const *base)
{
    unsigned long divisor = (unsigned long)my_strlen(base);
    int emitted = 0;
    int status;

    if (value >= divisor) {
        status = pf_base(value / divisor, base);
        if (status == -1) {
            return (-1);
        }
        emitted += status;
    }
    status = my_putchar(base[value % divisor]);
    if (status == -1) {
        return (-1);
    }
    return (emitted + status);
}

/**
** @brief Writes a %d or %i conversion: a signed decimal integer.
**
** INT_MIN cannot be negated as an int. Negating it as an unsigned
** value instead is always well defined and yields its magnitude.
**
** @param args The variadic arguments of my_printf.
**
** @return The number of bytes written, or -1 on failure.
*/
int pf_signed(va_list *args)
{
    int value = va_arg(*args, int);
    int status;

    if (value >= 0) {
        return (pf_base((unsigned long)value, "0123456789"));
    }
    status = my_putchar('-');
    if (status == -1) {
        return (-1);
    }
    status = pf_base(-(unsigned int)value, "0123456789");
    if (status == -1) {
        return (-1);
    }
    return (status + 1);
}

/**
** @brief Writes an %u, %o, %x or %X conversion.
**
** @param args The variadic arguments of my_printf.
** @param base The digits of the base, in order.
**
** @return The number of bytes written, or -1 on failure.
*/
int pf_unsigned(va_list *args, char const *base)
{
    unsigned int value = va_arg(*args, unsigned int);

    return (pf_base((unsigned long)value, base));
}
