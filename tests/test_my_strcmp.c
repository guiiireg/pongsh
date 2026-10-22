#include <criterion/criterion.h>
#include "../include/my.h"

Test(my_strcmp, test_strcmp_equal) {
    int result = my_strcmp("hello", "hello");
    cr_assert_eq(result, 0);
}

Test(my_strcmp, test_strcmp_less) {
    int result = my_strcmp("abc", "def");
    cr_assert_lt(result, 0);
}

Test(my_strcmp, test_strcmp_greater) {
    int result = my_strcmp("def", "abc");
    cr_assert_gt(result, 0);
}

Test(my_strcmp, test_strcmp_empty_equal) {
    int result = my_strcmp("", "");
    cr_assert_eq(result, 0);
}

Test(my_strcmp, test_strcmp_first_empty) {
    int result = my_strcmp("", "hello");
    cr_assert_lt(result, 0);
}

Test(my_strcmp, test_strcmp_second_empty) {
    int result = my_strcmp("hello", "");
    cr_assert_gt(result, 0);
}

Test(my_strcmp, test_strcmp_null_both) {
    int result = my_strcmp(NULL, NULL);
    cr_assert_eq(result, 0);
}

Test(my_strcmp, test_strcmp_null_first) {
    int result = my_strcmp(NULL, "hello");
    cr_assert_lt(result, 0);
}

Test(my_strcmp, test_strcmp_null_second) {
    int result = my_strcmp("hello", NULL);
    cr_assert_gt(result, 0);
}