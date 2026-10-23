#include <criterion/criterion.h>
#include "../include/my.h"

Test(my_strcapitalize, capitalizes_each_word)
{
    char str[32] = "hello world";

    cr_assert_eq(my_strcapitalize(str), str);
    cr_assert_str_eq(str, "Hello World");
}

Test(my_strcapitalize, lowercases_letters_after_first)
{
    char str[32] = "HELLO WORLD";

    my_strcapitalize(str);
    cr_assert_str_eq(str, "Hello World");
}

Test(my_strcapitalize, treats_digits_as_word_boundary)
{
    char str[32] = "42times 3rd";

    my_strcapitalize(str);
    cr_assert_str_eq(str, "42Times 3Rd");
}

Test(my_strcapitalize, handles_empty_string)
{
    char str[1] = "";

    my_strcapitalize(str);
    cr_assert_eq(str[0], '\0');
}
