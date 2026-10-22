#include <criterion/criterion.h>
#include <string.h>
#include "../include/my.h"

Test(my_strdup, test_strdup_basic) {
    char *dup = my_strdup("hello");
    cr_assert_not_null(dup);
    cr_assert_str_eq(dup, "hello");
    free(dup);
}

Test(my_strdup, test_strdup_empty) {
    char *dup = my_strdup("");
    cr_assert_not_null(dup);
    cr_assert_str_eq(dup, "");
    free(dup);
}

Test(my_strdup, test_strdup_with_spaces) {
    char *dup = my_strdup("hello world");
    cr_assert_not_null(dup);
    cr_assert_str_eq(dup, "hello world");
    free(dup);
}

Test(my_strdup, test_strdup_special_chars) {
    char *dup = my_strdup("!@#$%^&*()");
    cr_assert_not_null(dup);
    cr_assert_str_eq(dup, "!@#$%^&*()");
    free(dup);
}

Test(my_strdup, test_strdup_null) {
    char *dup = my_strdup(NULL);
    cr_assert_null(dup);
}