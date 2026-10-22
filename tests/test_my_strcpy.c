#include <criterion/criterion.h>
#include <string.h>
#include "../include/my.h"

Test(my_strcpy, test_strcpy_basic) {
    char dest[10];
    char *result = my_strcpy(dest, "hello");
    cr_assert_str_eq(result, "hello");
    cr_assert_str_eq(dest, "hello");
    cr_assert_eq(result, dest);
}

Test(my_strcpy, test_strcpy_empty) {
    char dest[10];
    char *result = my_strcpy(dest, "");
    cr_assert_str_eq(result, "");
    cr_assert_str_eq(dest, "");
}

Test(my_strcpy, test_strcpy_with_spaces) {
    char dest[20];
    char *result = my_strcpy(dest, "hello world");
    cr_assert_str_eq(result, "hello world");
}

Test(my_strcpy, test_strcpy_special_chars) {
    char dest[10];
    char *result = my_strcpy(dest, "!@#$%");
    cr_assert_str_eq(result, "!@#$%");
}

Test(my_strcpy, test_strcpy_null_dest) {
    char *result = my_strcpy(NULL, "test");
    cr_assert_eq(result, NULL);
}

Test(my_strcpy, test_strcpy_null_src) {
    char dest[10];
    char *result = my_strcpy(dest, NULL);
    cr_assert_eq(result, dest);
    cr_assert_str_eq(dest, "");
}