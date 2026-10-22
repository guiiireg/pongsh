#include <criterion/criterion.h>
#include "../include/my.h"

Test(my_strlen, test_strlen_hello) {
    int result = my_strlen("hello");
    cr_assert_eq(result, 5);
}

Test(my_strlen, test_strlen_empty) {
    int result = my_strlen("");
    cr_assert_eq(result, 0);
}

Test(my_strlen, test_strlen_with_spaces) {
    int result = my_strlen("hello world");
    cr_assert_eq(result, 11);
}

Test(my_strlen, test_strlen_special_chars) {
    int result = my_strlen("!@#$%^&*()");
    cr_assert_eq(result, 10);
}

Test(my_strlen, test_strlen_null) {
    int result = my_strlen(NULL);
    cr_assert_eq(result, 0);
}