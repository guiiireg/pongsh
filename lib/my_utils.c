/**
 * ============================================================================
 *                             UTILITY LIBRARY
 * ============================================================================
 * File: my_utils.c
 * Description: This file contains utility functions for converting between
 *              strings and integers.
 * Dependencies: pongsh.h
 * ============================================================================
 */

#include "../include/pongsh.h"

/**
 * @brief Skips whitespace characters in a string
 * @param str The string to process
 * @param i Pointer to current index
 */
static void skip_whitespace(const char *str, int *i)
{
    while (str[*i] == ' ' || str[*i] == '\t' || str[*i] == '\n' ||
        str[*i] == '\r' || str[*i] == '\f' || str[*i] == '\v')
        (*i)++;
}

/**
 * @brief Handles sign characters in a string
 * @param str The string to process
 * @param i Pointer to current index
 * @return Sign value (1 or -1)
 */
static int get_sign(const char *str, int *i)
{
    if (str[*i] == '-') {
        (*i)++;
        return -1;
    }
    if (str[*i] == '+')
        (*i)++;
    return 1;
}

/**
 * @brief Converts a string to an integer
 * @param str The string to convert
 * @return The converted integer value
 */
int my_atoi(const char *str)
{
    int result = 0;
    int sign;
    int i = 0;

    skip_whitespace(str, &i);
    sign = get_sign(str, &i);
    while (str[i] >= '0' && str[i] <= '9') {
        result = result * 10 + (str[i] - '0');
        i++;
    }
    return result * sign;
}

/**
 * @brief Counts the number of digits in an integer
 * @param value The integer to count digits for
 * @return Number of digits (including sign if negative)
 */
static int count_digits(int value)
{
    int len = 0;
    int temp = (value < 0) ? -value : value;

    if (value < 0)
        len++;
    if (temp == 0)
        return 1;
    while (temp > 0) {
        temp /= 10;
        len++;
    }
    return len;
}

/**
 * @brief Fills a string with the digits of an integer
 * @param str The string to fill
 * @param value The integer value
 * @param len The length of the string
 */
static void fill_digits(char *str, int value, int len)
{
    int temp = (value < 0) ? -value : value;
    int i = len - 1;

    str[len] = '\0';
    if (value == 0) {
        str[0] = '0';
        return;
    }
    while (temp > 0) {
        str[i] = (temp % 10) + '0';
        temp /= 10;
        i--;
    }
    if (value < 0)
        str[0] = '-';
}

/**
 * @brief Converts an integer to a string
 * @param value The integer to convert
 * @return A pointer to the converted string (must be freed)
 */
char *my_itoa(int value)
{
    char *str;
    int len = count_digits(value);

    str = my_malloc(len + 1);
    if (!str)
        return NULL;
    fill_digits(str, value, len);
    return str;
}
