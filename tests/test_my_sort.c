#include <criterion/criterion.h>

#include "my.h"

static int compare_int_ascending(void const *a, void const *b)
{
    return (*(const int *)a - *(const int *)b);
}

static int compare_int_descending(void const *a, void const *b)
{
    return (*(const int *)b - *(const int *)a);
}

Test(my_sort, sorts_integers_ascending)
{
    int array[5] = {5, 1, 4, 2, 3};

    my_sort(array, 5, (int)sizeof(int), compare_int_ascending);
    cr_assert_eq(array[0], 1);
    cr_assert_eq(array[2], 3);
    cr_assert_eq(array[4], 5);
}

Test(my_sort, sorts_integers_descending)
{
    int array[5] = {5, 1, 4, 2, 3};

    my_sort(array, 5, (int)sizeof(int), compare_int_descending);
    cr_assert_eq(array[0], 5);
    cr_assert_eq(array[2], 3);
    cr_assert_eq(array[4], 1);
}

static int compare_char(void const *a, void const *b)
{
    return (*(const char *)a - *(const char *)b);
}

Test(my_sort, sorts_characters)
{
    char array[5] = "pong";

    my_sort(array, 4, (int)sizeof(char), compare_char);
    cr_assert_str_eq(array, "gnop");
}

Test(my_sort, invalid_arguments)
{
    int array[2] = {2, 1};

    my_sort(NULL, 2, (int)sizeof(int), compare_int_ascending);
    my_sort(array, 0, (int)sizeof(int), compare_int_ascending);
    my_sort(array, -1, (int)sizeof(int), compare_int_ascending);
    my_sort(array, 2, 0, compare_int_ascending);
    cr_assert_eq(array[0], 2);
    cr_assert_eq(array[1], 1);
}
