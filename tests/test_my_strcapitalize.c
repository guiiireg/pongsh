#include <criterion/criterion.h>
#include "../include/my.h"

Test(my_strcapitalize, subject_example)
{
    char str[] = "hey, how are you? 42WORLd ....fitzgerald";
    char *ret = my_strcapitalize(str);

    cr_assert_eq(ret, str);
    cr_assert_str_eq(str, "Hey, How Are You? 42world ....Fitzgerald");
}

Test(my_strcapitalize, all_lowercase)
{
    char str[] = "hello world";
    char *ret = my_strcapitalize(str);

    cr_assert_eq(ret, str);
    cr_assert_str_eq(str, "Hello World");
}

Test(my_strcapitalize, all_uppercase)
{
    char str[] = "HELLO WORLD";
    char *ret = my_strcapitalize(str);

    cr_assert_eq(ret, str);
    cr_assert_str_eq(str, "Hello World");
}

Test(my_strcapitalize, mixed_case_words)
{
    char str[] = "tHiS iS a TeSt";
    char *ret = my_strcapitalize(str);

    cr_assert_eq(ret, str);
    cr_assert_str_eq(str, "This Is A Test");
}

Test(my_strcapitalize, words_separated_by_punctuation)
{
    char str[] = "+hello-world!foo";
    char *ret = my_strcapitalize(str);

    cr_assert_eq(ret, str);
    cr_assert_str_eq(str, "+Hello-World!Foo");
}

Test(my_strcapitalize, words_starting_with_numbers)
{
    char str[] = "42hello 1337WORLD";
    char *ret = my_strcapitalize(str);

    cr_assert_eq(ret, str);
    cr_assert_str_eq(str, "42hello 1337world");
}

Test(my_strcapitalize, empty_string)
{
    char str[] = "";
    char *ret = my_strcapitalize(str);

    cr_assert_eq(ret, str);
    cr_assert_str_eq(str, "");
}

Test(my_strcapitalize, single_letters)
{
    char str[] = "a b c D e";
    char *ret = my_strcapitalize(str);

    cr_assert_eq(ret, str);
    cr_assert_str_eq(str, "A B C D E");
}

Test(my_strcapitalize, no_letters)
{
    char str[] = "123 456 ... !@#";
    char *ret = my_strcapitalize(str);

    cr_assert_eq(ret, str);
    cr_assert_str_eq(str, "123 456 ... !@#");
}
