#include "my/my.h"

/**
 * @brief Swap the values of two integers.
 * @param a: first integer.
 * @param b: second integer.
 */
void my_swap(int *a, int *b)
{
    int tmp = *a;

    *a = *b;
    *b = tmp;
}
