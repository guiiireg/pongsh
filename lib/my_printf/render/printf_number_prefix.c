#include "my_printf_internal.h"

/**
 * @brief Computes the alternate form prefix of an unsigned value.
 *
 * @param spec The parsed specification.
 * @param magnitude The unsigned magnitude to write.
 * @param zeros The precision zero padding.
 * @param digits The number of digits that will be written.
 *
 * @return The prefix, possibly empty.
 */
static char const *pf_hash_prefix(pf_spec_t const *spec,
    unsigned long magnitude, int zeros, int digits)
{
    if (spec->spec == 'p') {
        return ("0x");
    }
    if (spec->hash == 0) {
        return ("");
    }
    switch (spec->spec) {
        case 'x':
            if (magnitude != 0) {
                return ("0x");
            }
            break;
        case 'X':
            if (magnitude != 0) {
                return ("0X");
            }
            break;
        case 'o':
            if (zeros == 0 && (magnitude != 0 || digits == 0)) {
                return ("0");
            }
            break;
        default:
            break;
    }
    return ("");
}

/**
 * @brief Computes the prefix of a number.
 *
 * The - and + signs take precedence over the space flag.
 *
 * @param spec The parsed specification.
 * @param magnitude The unsigned magnitude to write.
 * @param zeros The precision zero padding.
 * @param digits The number of digits that will be written.
 *
 * @return The prefix, possibly empty.
 */
char const *pf_number_prefix(pf_spec_t const *spec, unsigned long magnitude,
    int zeros, int digits)
{
    if (spec->negative) {
        return ("-");
    }
    switch (spec->spec) {
        case 'd':
        case 'i':
            if (spec->plus) {
                return ("+");
            }
            if (spec->space) {
                return (" ");
            }
            return ("");
        default:
            return (pf_hash_prefix(spec, magnitude, zeros, digits));
    }
}
