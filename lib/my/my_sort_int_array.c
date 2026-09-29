#include "../../include/my.h"

static void bubble_pass(int *tab, int size)
{
    for (int j = 0; j < size - 1; j++) {
        if (tab[j] > tab[j + 1])
            my_swap(&tab[j], &tab[j + 1]);
    }
}

/**
 * Sorts an integer array in ascending order.
 */
void my_sort_int_array(int *tab, int size)
{
    for (int i = 0; i < size - 1; i++) {
        bubble_pass(tab, size - 1);
    }
}
