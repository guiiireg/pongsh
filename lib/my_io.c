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

/**
 * @brief Writes a single character to standard output
 * @param c The character to write
 */
void my_putchar(char c)
{
    write(1, &c, 1);
}

/**
 * @brief Writes a string to standard output
 * @param str The string to write (must be null-terminated)
 * @return Number of characters written
 */
int my_putstr(const char *str)
{
    int i = 0;

    while (str[i])
        my_putchar(str[i++]);
    return i;
}

/**
 * @brief Writes an integer to standard output
 * @param nb The number to write
 * @return Number of characters written
 */
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

/**
 * @brief Calculates the length of a string
 * @param str The string to measure
 * @return The length of the string (excluding null terminator)
 */
int my_strlen(const char *str)
{
    int len = 0;

    while (str[len])
        len++;
    return len;
}
