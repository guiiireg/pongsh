#include <criterion/criterion.h>

#include "my.h"

Test(my_sort_word_array, sorts_words)
{
    char *array[4] = {"banana", "apple", "cherry", NULL};

    cr_assert_eq(my_sort_word_array(array), 0);
    cr_assert_str_eq(array[0], "apple");
    cr_assert_str_eq(array[1], "banana");
    cr_assert_str_eq(array[2], "cherry");
}

Test(my_sort_word_array, already_sorted)
{
    char *array[3] = {"a", "b", NULL};

    cr_assert_eq(my_sort_word_array(array), 0);
    cr_assert_str_eq(array[0], "a");
    cr_assert_str_eq(array[1], "b");
}

Test(my_sort_word_array, reverse_sorted)
{
    char *array[4] = {"c", "b", "a", NULL};

    cr_assert_eq(my_sort_word_array(array), 0);
    cr_assert_str_eq(array[0], "a");
    cr_assert_str_eq(array[2], "c");
}

Test(my_sort_word_array, empty_array)
{
    char *array[1] = {NULL};

    cr_assert_eq(my_sort_word_array(array), 0);
    cr_assert_null(array[0]);
}

Test(my_sort_word_array, null_input)
{
    cr_assert_eq(my_sort_word_array(NULL), -1);
}

Test(my_sort_word_array, sorted_result_is_usable)
{
    char **array = my_str_to_word_array("cherry banana apple");

    cr_assert_not_null(array);
    cr_assert_eq(my_sort_word_array(array), 0);
    cr_assert_str_eq(array[0], "apple");
    cr_assert_str_eq(array[1], "banana");
    cr_assert_str_eq(array[2], "cherry");
    my_free_word_array(array);
}
