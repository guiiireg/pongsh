#ifndef MY_PRINTF_INTERNAL_H_
    #define MY_PRINTF_INTERNAL_H_

#include <stdarg.h>

/*
 * Internal helpers of my_printf.
 *
 * These functions are shared between the my_printf source files and
 * are not part of the public libmy API. Their names are prefixed with
 * pf_ to avoid polluting the library namespace.
 *
 * Each writing helper returns the number of bytes written, or -1 on
 * failure, and advances the format index past what it consumed.
 */

#define PF_NOT_CONVERSION (-1)

/* The parsed fields of a conversion specification. */
typedef struct pf_spec_s {
    int left;
    int zero;
    int plus;
    int space;
    int hash;
    int negative;
    int width;
    int precision;
    int has_precision;
    char spec;
} pf_spec_t;

/* The computed layout of a number rendering. */
typedef struct pf_number_s {
    char const *prefix;
    char const *base;
    unsigned long magnitude;
    int zeros;
    int pad;
    int digits;
} pf_number_t;

int pf_parse(va_list *args, char const *format, int *index,
    pf_spec_t *spec);
void pf_parse_flags(char const *format, int *index, pf_spec_t *spec);
int pf_parse_width(va_list *args, char const *format, int *index,
    pf_spec_t *spec);
int pf_parse_precision(va_list *args, char const *format, int *index,
    pf_spec_t *spec);

int pf_percent(va_list *args, char const *format, int *index);
int pf_directive(va_list *args, char const *format, int *index);
int pf_format(va_list *args, char const *format);

int pf_run(va_list *args, pf_spec_t *spec);
int pf_render_char(va_list *args, pf_spec_t const *spec);
int pf_render_string(va_list *args, pf_spec_t const *spec);
int pf_render_number(va_list *args, pf_spec_t *spec);

int pf_base(unsigned long value, char const *base);
int pf_count_digits(unsigned long value, int base_len);
int pf_leading_zeros(pf_spec_t const *spec, unsigned long magnitude,
    char const *base);
char const *pf_number_prefix(pf_spec_t const *spec, unsigned long magnitude,
    int zeros, int digits);
int pf_write_number(pf_spec_t const *spec, unsigned long magnitude,
    char const *base);
int emit_number_left(pf_number_t const *number);
int emit_number_zero(pf_number_t const *number);
int emit_number_right(pf_number_t const *number);

int pf_add_status(int status, int total);
int pf_repeat(char c, int count);
int pf_write_chars(char const *str, int len);

#endif // MY_PRINTF_INTERNAL_H_
