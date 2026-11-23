#include "my_printf_internal.h"
#include <limits.h>
#include <unistd.h>

int my_printf_write(printf_output_t *out, char const *bytes, size_t length)
{
    ssize_t written;

    if (length > (size_t)(INT_MAX - out->count))
        return -1;
    while (length > 0) {
        written = write(STDOUT_FILENO, bytes, length);
        if (written <= 0)
            return -1;
        out->count += (int)written;
        bytes += written;
        length -= (size_t)written;
    }
    return 0;
}

static int write_repeat(printf_output_t *out, char byte, int count)
{
    char const spaces[] = "                                ";
    char const zeros[] = "00000000000000000000000000000000";
    char const *buffer = spaces;
    int chunk;

    if (byte == '0')
        buffer = zeros;
    while (count > 0) {
        chunk = count;
        if (chunk > (int)sizeof(spaces) - 1)
            chunk = sizeof(spaces) - 1;
        if (my_printf_write(out, buffer, (size_t)chunk) < 0)
            return -1;
        count -= chunk;
    }
    return 0;
}

static int write_field(printf_output_t *out, printf_field_t const *field)
{
    if (my_printf_write(out, field->prefix, (size_t)field->prefix_length) < 0)
        return -1;
    if (write_repeat(out, '0', field->zeros) < 0)
        return -1;
    return my_printf_write(out, field->text, (size_t)field->length);
}

int my_printf_field(printf_output_t *out, printf_spec_t const *spec,
    printf_field_t const *field)
{
    int padding = 0;
    int occupied;

    if (field->zeros > INT_MAX - field->length - field->prefix_length)
        return -1;
    occupied = field->length + field->prefix_length + field->zeros;
    if (spec->width > occupied)
        padding = spec->width - occupied;
    if (padding > INT_MAX - out->count - occupied)
        return -1;
    if (!(spec->flags & PRINTF_LEFT) && write_repeat(out, ' ', padding) < 0)
        return -1;
    if (write_field(out, field) < 0)
        return -1;
    if (spec->flags & PRINTF_LEFT)
        return write_repeat(out, ' ', padding);
    return 0;
}
