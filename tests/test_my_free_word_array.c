#include <criterion/criterion.h>

#include "my.h"

Test(my_free_word_array, frees_word_array)
{
    char **array = my_str_to_word_array("Hello world");

    cr_assert_not_null(array);
    my_free_word_array(array);
}

Test(my_free_word_array, frees_empty_array)
{
    char **array = my_str_to_word_array("");

    cr_assert_not_null(array);
    my_free_word_array(array);
}

Test(my_free_word_array, null_input)
{
    my_free_word_array(NULL);
}
