#include "my_printf_internal.h"

/**
 * @brief Checks whether a character is a flag.
 *
 * @param c The character to check.
 *
 * @return 1 if the character is a flag, 0 otherwise.
 */
static int pf_is_flag(char c)
{
    switch (c) {
        case '-':
        case '+':
        case ' ':
        case '0':
        case '#':
            return (1);
        default:
            return (0);
    }
}

/**
 * @brief Records one flag in the specification.
 *
 * @param flag The flag character.
 * @param spec The specification being parsed.
 */
static void pf_set_flag(char flag, pf_spec_t *spec)
{
    switch (flag) {
        case '-':
            spec->left = 1;
            break;
        case '+':
            spec->plus = 1;
            break;
        case ' ':
            spec->space = 1;
            break;
        case '0':
            spec->zero = 1;
            break;
        case '#':
            spec->hash = 1;
            break;
        default:
            break;
    }
}

/**
 * @brief Parses the flags of a conversion specification.
 *
 * @param format The format string being parsed.
 * @param index The current position, advanced past the flags.
 * @param spec The specification being parsed.
 */
void pf_parse_flags(char const *format, int *index, pf_spec_t *spec)
{
    while (pf_is_flag(format[*index]) == 1) {
        pf_set_flag(format[*index], spec);
        *index += 1;
    }
}
