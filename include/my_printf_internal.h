#ifndef MY_PRINTF_INTERNAL_H
    #define MY_PRINTF_INTERNAL_H

    #include <stdarg.h>
    #include <stddef.h>
    #include <stdint.h>

enum printf_flag {
    PRINTF_LEFT = 1,
    PRINTF_PLUS = 2,
    PRINTF_SPACE = 4,
    PRINTF_ALT = 8,
    PRINTF_ZERO = 16
};

enum printf_length {
    PRINTF_DEFAULT, PRINTF_HH, PRINTF_H, PRINTF_L, PRINTF_LL, PRINTF_J
};

typedef struct printf_spec {
    unsigned int flags;
    int width;
    int precision;
    enum printf_length length;
    char type;
} printf_spec_t;

typedef struct printf_output {
    int count;
} printf_output_t;

typedef struct printf_field {
    char const *text;
    int length;
    char const *prefix;
    int prefix_length;
    int zeros;
} printf_field_t;

int my_printf_parse(char const **format, printf_spec_t *spec, va_list *args);
int my_printf_write(printf_output_t *out, char const *bytes, size_t length);
int my_printf_field(printf_output_t *out, printf_spec_t const *spec,
    printf_field_t const *field);
int my_printf_integer(printf_output_t *out, printf_spec_t const *spec,
    va_list *args);

int my_printf_read_dimensions(char const **format, printf_spec_t *spec,
    va_list *args);
int my_printf_read_integer(printf_field_t *field, printf_spec_t const *spec,
    va_list *args, uintmax_t *value);

#endif
