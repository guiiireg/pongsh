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
