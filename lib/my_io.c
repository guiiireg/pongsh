/**
 * ============================================================================
 *                              BASIC I/O LIBRARY
 * ============================================================================
 * File: my_io.c
 * Description: This file contains fundamental I/O functions including
 *          character, output, string output, and number formatting operations.
 * Dependencies: unistd.h (for write system call), pongsh.h
 * ============================================================================
 */

#include "../include/pongsh.h"

void my_putchar(char c)
{
    write(1, &c, 1);
}

int my_putstr(const char *str)
{
    int i = 0;

    while (str[i])
        my_putchar(str[i++]);
    return i;
}

int my_putnbr(int nb)
{
    int count = 0;

    if (nb == -2147483648) {
        count += my_putstr("-2147483648");
        return count;
    }
    if (nb < 0) {
        my_putchar('-');
        nb = -nb;
        count++;
    }
    if (nb >= 10)
        count += my_putnbr(nb / 10);
    my_putchar((nb % 10) + '0');
    return count + 1;
}

int my_strlen(const char *str)
{
    int len = 0;

    while (str[len])
        len++;
    return len;
}
