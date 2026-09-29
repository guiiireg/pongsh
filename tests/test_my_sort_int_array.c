#include <criterion/criterion.h>
#include "../include/my.h"

Test(my_sort_int_array, standard_unsorted)
{
    int tab[] = {5, 2, 8, 1, 9};
    int expected[] = {1, 2, 5, 8, 9};

    my_sort_int_array(tab, 5);
    cr_assert_arr_eq(tab, expected, 5);
}

Test(my_sort_int_array, already_sorted)
{
    int tab[] = {1, 2, 3, 4, 5};
    int expected[] = {1, 2, 3, 4, 5};

    my_sort_int_array(tab, 5);
    cr_assert_arr_eq(tab, expected, 5);
}

Test(my_sort_int_array, reverse_sorted)
{
    int tab[] = {5, 4, 3, 2, 1};
    int expected[] = {1, 2, 3, 4, 5};

    my_sort_int_array(tab, 5);
    cr_assert_arr_eq(tab, expected, 5);
}

Test(my_sort_int_array, with_negative_numbers)
{
    int tab[] = {-3, 10, -50, 0, 7};
    int expected[] = {-50, -3, 0, 7, 10};

    my_sort_int_array(tab, 5);
    cr_assert_arr_eq(tab, expected, 5);
}

Test(my_sort_int_array, with_duplicates)
{
    int tab[] = {4, 2, 4, 1, 2};
    int expected[] = {1, 2, 2, 4, 4};

    my_sort_int_array(tab, 5);
    cr_assert_arr_eq(tab, expected, 5);
}

Test(my_sort_int_array, all_same_elements)
{
    int tab[] = {7, 7, 7, 7};
    int expected[] = {7, 7, 7, 7};

    my_sort_int_array(tab, 4);
    cr_assert_arr_eq(tab, expected, 4);
}

Test(my_sort_int_array, single_element)
{
    int tab[] = {42};
    int expected[] = {42};

    my_sort_int_array(tab, 1);
    cr_assert_arr_eq(tab, expected, 1);
}

Test(my_sort_int_array, zero_size)
{
    int tab[] = {42};

    my_sort_int_array(tab, 0);
    cr_assert_eq(tab[0], 42);
}

Test(my_sort_int_array, two_elements)
{
    int tab[] = {99, 11};
    int expected[] = {11, 99};

    my_sort_int_array(tab, 2);
    cr_assert_arr_eq(tab, expected, 2);
}
