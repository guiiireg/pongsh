#include "my.h"

void my_sort_int_array(int *tab, int size)
{
    int position;

    for (int index = 1; index < size; index++) {
        position = index;
        while (position > 0 && tab[position - 1] > tab[position]) {
            my_swap(&tab[position - 1], &tab[position]);
            position--;
        }
    }
}
