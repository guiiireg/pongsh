#include <criterion/criterion.h>
#include "../include/shell.h"

Test(split_words, null_string)
{
    cr_assert_null(split_words(NULL));
}

Test(split_words, single_word)
{
    char **argv = split_words("echo");

    cr_assert_not_null(argv);
    cr_assert_str_eq(argv[0], "echo");
    cr_assert_null(argv[1]);
    free_word_array(argv);
}

Test(split_words, multiple_words_with_delimiters)
{
    char **argv = split_words("\t  echo   hello \t world  ");

    cr_assert_not_null(argv);
    cr_assert_str_eq(argv[0], "echo");
    cr_assert_str_eq(argv[1], "hello");
    cr_assert_str_eq(argv[2], "world");
    cr_assert_null(argv[3]);
    free_word_array(argv);
}

Test(free_word_array, null_array)
{
    free_word_array(NULL);
}
