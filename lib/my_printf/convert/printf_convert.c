#include "my_printf_internal.h"

/**
 * @brief Runs the rendering matching the parsed specification.
 *
 * @param args The variadic arguments of my_printf.
 * @param spec The parsed specification.
 *
 * @return The number of bytes written, or -1 on failure.
 */
int pf_run(va_list *args, pf_spec_t *spec)
{
    switch (spec->spec) {
        case 'c':
            return (pf_render_char(args, spec));
        case 's':
            return (pf_render_string(args, spec));
        case 'd':
        case 'i':
        case 'u':
        case 'o':
        case 'x':
        case 'X':
        case 'p':
            return (pf_render_number(args, spec));
        default:
            return (-1);
    }
}
