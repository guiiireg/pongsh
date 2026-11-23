#include "my.h"

static void show_hex(unsigned int value, int digits)
{
    static char const hex[] = "0123456789abcdef";

    for (int shift = (digits - 1) * 4; shift >= 0; shift -= 4)
        my_putchar(hex[(value >> shift) & 15]);
}

static void show_bytes(char const *str, int count)
{
    for (int index = 0; index < 16; index++) {
        if (index < count)
            show_hex((unsigned char)str[index], 2);
        else
            my_putstr("  ");
        if (index % 2 == 1)
            my_putchar(' ');
    }
}

static void show_printable(char const *str, int count)
{
    unsigned char byte;

    for (int index = 0; index < count; index++) {
        byte = (unsigned char)str[index];
        my_putchar(byte >= 32 && byte <= 126 ? byte : '.');
    }
}

int my_showmem(char const *str, int size)
{
    int count;
    int offset = 0;

    while (offset < size) {
        count = size - offset;
        if (count > 16)
            count = 16;
        show_hex(offset, 8);
        my_putstr(": ");
        show_bytes(str + offset, count);
        my_putchar(' ');
        show_printable(str + offset, count);
        my_putchar('\n');
        offset += count;
    }
    return 0;
}
