#include <stddef.h>

#include "my.h"
#include "my_printf_internal.h"

/**
 * @brief Writes a character, left aligned in its field.
 *
 * @param c The character to write.
 * @param pad The number of trailing spaces.
 *
 * @return The number of bytes written, or -1 on failure.
 */
static int emit_char_left(char c, int pad)
{
    int total = my_putchar(c);

    if (total != -1) {
        total = pf_add_status(pf_repeat(' ', pad), total);
    }
    return (total);
}

/**
 * @brief Writes a character, right aligned in its field.
 *
 * @param c The character to write.
 * @param pad The number of leading spaces.
 *
 * @return The number of bytes written, or -1 on failure.
 */
static int emit_char_right(char c, int pad)
{
    int total = pf_repeat(' ', pad);

    if (total != -1) {
        total = pf_add_status(my_putchar(c), total);
    }
    return (total);
}

/**
 * @brief Renders a %c conversion.
 *
 * The int argument is converted to an unsigned char. The 0 flag is
 * undefined for this conversion and is ignored.
 *
 * @param args The variadic arguments of my_printf.
 * @param spec The parsed specification.
 *
 * @return The number of bytes written, or -1 on failure.
 */
int pf_render_char(va_list *args, pf_spec_t const *spec)
{
    char c = (char)va_arg(*args, int);
    int pad = 0;

    if (spec->width > 1) {
        pad = spec->width - 1;
    }
    if (spec->left) {
        return (emit_char_left(c, pad));
    }
    return (emit_char_right(c, pad));
}

/**
 * @brief Writes a string, left aligned in its field.
 *
 * @param str The string to write.
 * @param len The number of characters to write.
 * @param pad The number of trailing spaces.
 *
 * @return The number of bytes written, or -1 on failure.
 */
static int emit_string_left(char const *str, int len, int pad)
{
    int total = pf_write_chars(str, len);

    if (total != -1) {
        total = pf_add_status(pf_repeat(' ', pad), total);
    }
    return (total);
}

/**
 * @brief Writes a string, right aligned in its field.
 *
 * @param str The string to write.
 * @param len The number of characters to write.
 * @param pad The number of leading spaces.
 *
 * @return The number of bytes written, or -1 on failure.
 */
static int emit_string_right(char const *str, int len, int pad)
{
    int total = pf_repeat(' ', pad);

    if (total != -1) {
        total = pf_add_status(pf_write_chars(str, len), total);
    }
    return (total);
}

/**
 * @brief Renders a %s conversion.
 *
 * A NULL argument is printed as (null), like glibc does. The
 * precision truncates the string; the width never does.
 *
 * @param args The variadic arguments of my_printf.
 * @param spec The parsed specification.
 *
 * @return The number of bytes written, or -1 on failure.
 */
int pf_render_string(va_list *args, pf_spec_t const *spec)
{
    char const *str = va_arg(*args, char const *);
    int len;
    int pad = 0;

    if (str == NULL) {
        str = "(null)";
    }
    len = my_strlen(str);
    if (spec->has_precision && spec->precision < len) {
        len = spec->precision;
    }
    if (spec->width > len) {
        pad = spec->width - len;
    }
    if (spec->left) {
        return (emit_string_left(str, len, pad));
    }
    return (emit_string_right(str, len, pad));
}
