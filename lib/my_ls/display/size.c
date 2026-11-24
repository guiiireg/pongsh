#include "my_ls.h"
#include "my.h"

size_t ls_decimal(char *text, uintmax_t value)
{
    char reversed[LS_SIZE_BUFFER];
    size_t count = 0;
    size_t index;

    do {
        reversed[count] = '0' + value % 10;
        value /= 10;
        count++;
    } while (value);
    for (index = 0; index < count; index++)
        text[index] = reversed[count - 1 - index];
    text[count] = '\0';
    return count;
}

static size_t human_digits(char *text, uintmax_t whole, unsigned int tenths)
{
    size_t length = ls_decimal(text, whole);

    if (whole < 10) {
        text[length] = ',';
        text[length + 1] = '0' + tenths;
        length += 2;
    }
    return length;
}

static uintmax_t size_unit(uintmax_t value, char const **suffix)
{
    uintmax_t unit = 1;

    while (value / unit >= LS_SIZE_BASE && (*suffix)[1]) {
        unit *= LS_SIZE_BASE;
        (*suffix)++;
    }
    return unit;
}

static unsigned int rounded_fraction(uintmax_t *whole, uintmax_t value,
    uintmax_t unit)
{
    uintmax_t remainder = value % unit;
    uintmax_t tenth = unit / 10;
    unsigned int tenths = 0;

    if (*whole < 10) {
        tenths = remainder / tenth + (remainder % tenth >= tenth / 2);
        if (tenths < 10)
            return tenths;
        (*whole)++;
    } else if (remainder >= unit / 2) {
        (*whole)++;
    }
    return 0;
}

static void human_size(char *text, uintmax_t value)
{
    char const *suffix = " kMGTPEZYRQ";
    uintmax_t unit = size_unit(value, &suffix);
    uintmax_t whole = value / unit;
    unsigned int tenths;
    size_t length;

    if (unit == 1) {
        ls_decimal(text, value);
        return;
    }
    tenths = rounded_fraction(&whole, value, unit);
    if (whole == LS_SIZE_BASE && suffix[1]) {
        whole = 1;
        tenths = 0;
        suffix++;
    }
    length = human_digits(text, whole, tenths);
    text[length] = *suffix;
    text[length + 1] = '\0';
}

void ls_size(char *text, struct stat const *info)
{
    if (S_ISDIR(info->st_mode) || info->st_size < 0) {
        my_strcpy(text, "-");
        return;
    }
    human_size(text, (uintmax_t)info->st_size);
}
