#ifndef MY_PRINTF_INTERNAL_H
    #define MY_PRINTF_INTERNAL_H

    #include <stdarg.h>
    #include <stddef.h>
    #include <stdint.h>

    #define PRINTF_READ_INTMAX(args) va_arg(*(args), intmax_t)
    #define PRINTF_READ_UINTMAX(args) va_arg(*(args), uintmax_t)

enum printf_flag {
    PRINTF_LEFT = 1,
    PRINTF_PLUS = 2,
    PRINTF_SPACE = 4,
    PRINTF_ALT = 8,
    PRINTF_ZERO = 16
};

typedef enum printf_length_e {
    PRINTF_DEFAULT,
    PRINTF_HH,
    PRINTF_H,
    PRINTF_L,
    PRINTF_LL,
    PRINTF_J
} printf_length_t;

typedef struct printf_spec_s {
    unsigned int flags;
    int width;
    int precision;
    printf_length_t length;
    char type;
} printf_spec_t;

typedef struct printf_field_s {
    const char *text;
    int length;
    const char *prefix;
    int prefix_length;
    int zeros;
} printf_field_t;

int my_printf_parse(char const **format, printf_spec_t *spec, va_list *args);
int my_printf_write(int *out, char const *bytes, size_t length);
int my_printf_field(int *out, printf_spec_t const *spec,
    printf_field_t const *field);
int my_printf_integer(int *out, printf_spec_t const *spec,
    va_list *args);

int my_printf_read_dimensions(char const **format, printf_spec_t *spec,
    va_list *args);
int my_printf_read_integer(printf_field_t *field, printf_spec_t const *spec,
    va_list *args, uintmax_t *value);

#endif
