#include <criterion/criterion.h>

#include "my.h"

Test(my_str_to_word_array, basic)
{
    char **array = my_str_to_word_array("Hello world");

    cr_assert_not_null(array);
    cr_assert_str_eq(array[0], "Hello");
    cr_assert_str_eq(array[1], "world");
    cr_assert_null(array[2]);
    my_free_word_array(array);
}

Test(my_str_to_word_array, multiple_separators)
{
    char **array = my_str_to_word_array("  Hello \t\t world  ");

    cr_assert_not_null(array);
    cr_assert_str_eq(array[0], "Hello");
    cr_assert_str_eq(array[1], "world");
    cr_assert_null(array[2]);
    my_free_word_array(array);
}

Test(my_str_to_word_array, newlines_are_separators)
{
    char **array = my_str_to_word_array("one\ntwo\nthree");

    cr_assert_not_null(array);
    cr_assert_str_eq(array[0], "one");
    cr_assert_str_eq(array[2], "three");
    cr_assert_null(array[3]);
    my_free_word_array(array);
}

Test(my_str_to_word_array, single_word)
{
    char **array = my_str_to_word_array("pongsh");

    cr_assert_not_null(array);
    cr_assert_str_eq(array[0], "pongsh");
    cr_assert_null(array[1]);
    my_free_word_array(array);
}

Test(my_str_to_word_array, empty_string)
{
    char **array = my_str_to_word_array("");

    cr_assert_not_null(array);
    cr_assert_null(array[0]);
    my_free_word_array(array);
}

Test(my_str_to_word_array, only_separators)
{
    char **array = my_str_to_word_array(" \t\n ");

    cr_assert_not_null(array);
    cr_assert_null(array[0]);
    my_free_word_array(array);
}

Test(my_str_to_word_array, null_input)
{
    cr_assert_null(my_str_to_word_array(NULL));
}
