#include <stddef.h>

#include "my.h"
#include "my_printf_internal.h"

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
 * @brief Computes the printed length of a NULL string.
 *
 * Like glibc, a NULL string prints (null), but nothing at all when
 * the precision is too small to fit it.
 *
 * @param spec The parsed specification.
 *
 * @return The number of characters printed for a NULL string.
 */
static int pf_null_string_len(pf_spec_t const *spec)
{
    if (spec->has_precision && spec->precision < 6) {
        return (0);
    }
    return (6);
}

/**
 * @brief Renders a %s conversion.
 *
 * A NULL argument is printed as (null), like glibc does: the whole
 * literal, or nothing when the precision is below 6. The precision
 * truncates the string; the width never does.
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
        len = pf_null_string_len(spec);
    } else {
        len = my_strlen(str);
    }
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
