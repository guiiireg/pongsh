#include <criterion/criterion.h>
#include <string.h>
#include "../include/my.h"

Test(my_strcat, test_strcat_basic) {
    char dest[20] = "hello";
    char *result = my_strcat(dest, " world");
    cr_assert_str_eq(result, "hello world");
    cr_assert_str_eq(dest, "hello world");
    cr_assert_eq(result, dest);
}

Test(my_strcat, test_strcat_empty_src) {
    char dest[20] = "hello";
    char *result = my_strcat(dest, "");
    cr_assert_str_eq(result, "hello");
    cr_assert_str_eq(dest, "hello");
}

Test(my_strcat, test_strcat_empty_dest) {
    char dest[20] = "";
    char *result = my_strcat(dest, "world");
    cr_assert_str_eq(result, "world");
    cr_assert_str_eq(dest, "world");
}

Test(my_strcat, test_strcat_both_empty) {
    char dest[20] = "";
    char *result = my_strcat(dest, "");
    cr_assert_str_eq(result, "");
    cr_assert_str_eq(dest, "");
}

Test(my_strcat, test_strcat_null_dest) {
    char *result = my_strcat(NULL, "world");
    cr_assert_eq(result, NULL);
}

Test(my_strcat, test_strcat_null_src) {
    char dest[20] = "hello";
    char *result = my_strcat(dest, NULL);
    cr_assert_str_eq(result, "hello");
    cr_assert_str_eq(dest, "hello");
}

Test(my_strcat, test_strcat_null_both) {
    char *result = my_strcat(NULL, NULL);
    cr_assert_eq(result, NULL);
}