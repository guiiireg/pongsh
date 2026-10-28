#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "my.h"

Test(my_show_word_array, displays_words, .init = cr_redirect_stdout)
{
    char *words[3] = {"Hello", "World", NULL};

    cr_assert_eq(my_show_word_array(words), 2);
    cr_assert_stdout_eq_str("Hello\nWorld\n");
}

Test(my_show_word_array, empty_array, .init = cr_redirect_stdout)
{
    char *words[1] = {NULL};

    cr_assert_eq(my_show_word_array(words), 0);
    cr_assert_stdout_eq_str("");
}

Test(my_show_word_array, null_input)
{
    cr_assert_eq(my_show_word_array(NULL), -1);
}
