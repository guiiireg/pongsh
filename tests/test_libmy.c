#define _POSIX_C_SOURCE 200809L

#include "my.h"
#include "unity.h"
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

static FILE *captured_output;
static int saved_stdout = -1;

void setUp(void)
{
}

static int restore_stdout(void)
{
    int result = dup2(saved_stdout, STDOUT_FILENO);

    close(saved_stdout);
    saved_stdout = -1;
    return result;
}

void tearDown(void)
{
    int result = STDOUT_FILENO;

    if (saved_stdout >= 0)
        result = restore_stdout();
    if (captured_output) {
        fclose(captured_output);
        captured_output = NULL;
    }
    TEST_ASSERT_EQUAL_INT(STDOUT_FILENO, result);
}

static void start_capture(void)
{
    captured_output = tmpfile();
    TEST_ASSERT_NOT_NULL(captured_output);
    TEST_ASSERT_EQUAL_INT(0, fflush(stdout));
    saved_stdout = dup(STDOUT_FILENO);
    TEST_ASSERT_TRUE(saved_stdout >= 0);
    TEST_ASSERT_EQUAL_INT(STDOUT_FILENO,
        dup2(fileno(captured_output), STDOUT_FILENO));
}

static void expect_output(char const *expected, size_t length)
{
    char actual[256];
    size_t count;

    TEST_ASSERT_EQUAL_INT(0, fflush(stdout));
    TEST_ASSERT_EQUAL_INT(STDOUT_FILENO, restore_stdout());
    TEST_ASSERT_EQUAL_INT(0, fseek(captured_output, 0, SEEK_SET));
    count = fread(actual, 1, sizeof(actual), captured_output);
    TEST_ASSERT_EQUAL_INT(0, ferror(captured_output));
    TEST_ASSERT_EQUAL_UINT(length, count);
    if (length > 0)
        TEST_ASSERT_EQUAL_MEMORY(expected, actual, length);
}

static void test_my_swap(void)
{
    int a = 1;
    int b = -2;

    my_swap(&a, &b);
    TEST_ASSERT_EQUAL_INT(-2, a);
    TEST_ASSERT_EQUAL_INT(1, b);
    my_swap(&a, &a);
    TEST_ASSERT_EQUAL_INT(-2, a);
}

static void test_my_strlen(void)
{
    TEST_ASSERT_EQUAL_INT(0, my_strlen(""));
    TEST_ASSERT_EQUAL_INT(4, my_strlen("ab c"));
    TEST_ASSERT_EQUAL_INT(2, my_strlen("ab\0cd"));
}

static void test_my_getnbr(void)
{
    TEST_ASSERT_EQUAL_INT(-42, my_getnbr("+--+-42tail"));
    TEST_ASSERT_EQUAL_INT(42, my_getnbr("--42"));
    TEST_ASSERT_EQUAL_INT(0, my_getnbr("+-"));
}

static void test_my_getnbr_limits(void)
{
    char text[sizeof(int) * CHAR_BIT + 4];

    snprintf(text, sizeof(text), "%d", INT_MAX);
    TEST_ASSERT_EQUAL_INT(INT_MAX, my_getnbr(text));
    snprintf(text, sizeof(text), "%d", INT_MIN);
    TEST_ASSERT_EQUAL_INT(INT_MIN, my_getnbr(text));
    snprintf(text, sizeof(text), "%d0", INT_MAX);
    TEST_ASSERT_EQUAL_INT(0, my_getnbr(text));
    snprintf(text, sizeof(text), "%d0", INT_MIN);
    TEST_ASSERT_EQUAL_INT(0, my_getnbr(text));
}

static void test_my_sort_int_array(void)
{
    int values[] = {INT_MAX, 0, -2, 0, INT_MIN};
    int expected[] = {INT_MIN, -2, 0, 0, INT_MAX};

    my_sort_int_array(values, 0);
    TEST_ASSERT_EQUAL_INT(INT_MAX, values[0]);
    my_sort_int_array(values, 5);
    TEST_ASSERT_EQUAL_INT_ARRAY(expected, values, 5);
}

static void test_my_compute_power_rec(void)
{
    TEST_ASSERT_EQUAL_INT(-8, my_compute_power_rec(-2, 3));
    TEST_ASSERT_EQUAL_INT(16, my_compute_power_rec(-2, 4));
    TEST_ASSERT_EQUAL_INT(1, my_compute_power_rec(0, 0));
    TEST_ASSERT_EQUAL_INT(0, my_compute_power_rec(2, -1));
    TEST_ASSERT_EQUAL_INT(INT_MIN, my_compute_power_rec(INT_MIN, 1));
    TEST_ASSERT_EQUAL_INT(0, my_compute_power_rec(INT_MAX, 2));
}

static void test_my_compute_square_root(void)
{
    TEST_ASSERT_EQUAL_INT(0, my_compute_square_root(-1));
    TEST_ASSERT_EQUAL_INT(0, my_compute_square_root(0));
    TEST_ASSERT_EQUAL_INT(1, my_compute_square_root(1));
    TEST_ASSERT_EQUAL_INT(0, my_compute_square_root(99));
    TEST_ASSERT_EQUAL_INT(100, my_compute_square_root(10000));
}

static void test_my_is_prime(void)
{
    TEST_ASSERT_EQUAL_INT(0, my_is_prime(1));
    TEST_ASSERT_EQUAL_INT(0, my_is_prime(-7));
    TEST_ASSERT_EQUAL_INT(0, my_is_prime(49));
    TEST_ASSERT_EQUAL_INT(1, my_is_prime(2));
    TEST_ASSERT_EQUAL_INT(1, my_is_prime(97));
}

static void test_my_find_prime_sup(void)
{
    TEST_ASSERT_EQUAL_INT(2, my_find_prime_sup(INT_MIN));
    TEST_ASSERT_EQUAL_INT(23, my_find_prime_sup(20));
    TEST_ASSERT_EQUAL_INT(23, my_find_prime_sup(23));
    TEST_ASSERT_EQUAL_INT(29, my_find_prime_sup(24));
}

static void test_my_strcpy(void)
{
    char dest[] = "xxxxx";

    TEST_ASSERT_EQUAL_PTR(dest, my_strcpy(dest, "ab"));
    TEST_ASSERT_EQUAL_STRING("ab", dest);
    TEST_ASSERT_EQUAL_CHAR('x', dest[3]);
    my_strcpy(dest, "");
    TEST_ASSERT_EQUAL_STRING("", dest);
}

static void test_my_strncpy(void)
{
    char dest[] = "xxxxx";

    TEST_ASSERT_EQUAL_PTR(dest, my_strncpy(dest, "a", 4));
    TEST_ASSERT_EQUAL_MEMORY("a\0\0\0x", dest, 5);
    my_strncpy(dest, "bcd", 2);
    TEST_ASSERT_EQUAL_STRING("bc", dest);
    my_strncpy(dest, "z", 0);
    TEST_ASSERT_EQUAL_STRING("bc", dest);
}

static void test_my_revstr(void)
{
    char odd[] = "abc";
    char even[] = "abcd";
    char empty[] = "";

    TEST_ASSERT_EQUAL_PTR(odd, my_revstr(odd));
    TEST_ASSERT_EQUAL_STRING("cba", odd);
    TEST_ASSERT_EQUAL_STRING("dcba", my_revstr(even));
    TEST_ASSERT_EQUAL_STRING("", my_revstr(empty));
}

static void test_my_strstr(void)
{
    char str[] = "aaab aab";

    TEST_ASSERT_EQUAL_PTR(str + 1, my_strstr(str, "aab"));
    TEST_ASSERT_EQUAL_PTR(str, my_strstr(str, ""));
    TEST_ASSERT_NULL(my_strstr(str, "aabb"));
    TEST_ASSERT_NULL(my_strstr(str + 8, "a"));
}

static void test_my_strcmp(void)
{
    TEST_ASSERT_EQUAL_INT(0, my_strcmp("ab", "ab"));
    TEST_ASSERT_TRUE(my_strcmp("ab", "abc") < 0);
    TEST_ASSERT_TRUE(my_strcmp("\377", "\001") > 0);
}

static void test_my_strncmp(void)
{
    TEST_ASSERT_EQUAL_INT(0, my_strncmp("ab", "ac", 1));
    TEST_ASSERT_EQUAL_INT(0, my_strncmp("ab", "cd", 0));
    TEST_ASSERT_EQUAL_INT(0, my_strncmp("ab", "ab", 8));
    TEST_ASSERT_TRUE(my_strncmp("ab", "ac", 2) < 0);
    TEST_ASSERT_TRUE(my_strncmp("\377", "\001", 1) > 0);
}

static void test_my_strupcase(void)
{
    char str[] = "aZ m9!";

    TEST_ASSERT_EQUAL_PTR(str, my_strupcase(str));
    TEST_ASSERT_EQUAL_STRING("AZ M9!", str);
}

static void test_my_strlowcase(void)
{
    char str[] = "aZ M9!";

    TEST_ASSERT_EQUAL_PTR(str, my_strlowcase(str));
    TEST_ASSERT_EQUAL_STRING("az m9!", str);
}

static void test_my_strcapitalize(void)
{
    char str[] = "hELLO, wORLD+again 42FOO";

    TEST_ASSERT_EQUAL_PTR(str, my_strcapitalize(str));
    TEST_ASSERT_EQUAL_STRING("Hello, World+Again 42foo", str);
}

static void test_my_str_isalpha(void)
{
    TEST_ASSERT_EQUAL_INT(1, my_str_isalpha(""));
    TEST_ASSERT_EQUAL_INT(1, my_str_isalpha("Az"));
    TEST_ASSERT_EQUAL_INT(0, my_str_isalpha("A1"));
}

static void test_my_str_isnum(void)
{
    TEST_ASSERT_EQUAL_INT(1, my_str_isnum(""));
    TEST_ASSERT_EQUAL_INT(1, my_str_isnum("019"));
    TEST_ASSERT_EQUAL_INT(0, my_str_isnum("-1"));
}

static void test_my_str_islower(void)
{
    TEST_ASSERT_EQUAL_INT(1, my_str_islower(""));
    TEST_ASSERT_EQUAL_INT(1, my_str_islower("az"));
    TEST_ASSERT_EQUAL_INT(0, my_str_islower("aZ"));
}

static void test_my_str_isupper(void)
{
    TEST_ASSERT_EQUAL_INT(1, my_str_isupper(""));
    TEST_ASSERT_EQUAL_INT(1, my_str_isupper("AZ"));
    TEST_ASSERT_EQUAL_INT(0, my_str_isupper("Az"));
}

static void test_my_str_isprintable(void)
{
    TEST_ASSERT_EQUAL_INT(1, my_str_isprintable(""));
    TEST_ASSERT_EQUAL_INT(1, my_str_isprintable(" !~"));
    TEST_ASSERT_EQUAL_INT(0, my_str_isprintable("\177"));
}

static void test_my_strcat(void)
{
    char dest[12] = "ab";

    TEST_ASSERT_EQUAL_PTR(dest, my_strcat(dest, "cd"));
    TEST_ASSERT_EQUAL_STRING("abcd", dest);
    TEST_ASSERT_EQUAL_STRING("abcd", my_strcat(dest, ""));
}

static void test_my_strncat(void)
{
    char dest[12] = "ab";

    TEST_ASSERT_EQUAL_PTR(dest, my_strncat(dest, "cde", 2));
    TEST_ASSERT_EQUAL_STRING("abcd", dest);
    TEST_ASSERT_EQUAL_STRING("abcd", my_strncat(dest, "x", 0));
    TEST_ASSERT_EQUAL_STRING("abcdf", my_strncat(dest, "f", 3));
}

static void test_my_putchar(void)
{
    start_capture();
    my_putchar('A');
    my_putchar('\0');
    expect_output("A\0", 2);
}

static void test_my_isneg(void)
{
    start_capture();
    my_isneg(INT_MIN);
    my_isneg(0);
    my_isneg(INT_MAX);
    expect_output("NPP", 3);
}

static void test_my_put_nbr(void)
{
    char expected[sizeof(int) * CHAR_BIT + 8];

    snprintf(expected, sizeof(expected), "%d 0 42", INT_MIN);
    start_capture();
    my_put_nbr(INT_MIN);
    my_putchar(' ');
    my_put_nbr(0);
    my_putchar(' ');
    my_put_nbr(42);
    expect_output(expected, strlen(expected));
}

static void test_my_putstr(void)
{
    start_capture();
    my_putstr("");
    my_putstr("ab\n");
    expect_output("ab\n", 3);
}

static void test_my_showstr(void)
{
    char const expected[] = "A\\0a\\7f\\ff~";

    start_capture();
    my_showstr("");
    my_showstr("A\n\177\377~");
    expect_output(expected, sizeof(expected) - 1);
}

static void test_my_showmem(void)
{
    char const bytes[] = "ABCDEFGHIJKLMNOP\0\377";
    char const expected[] =
        "00000000: 4142 4344 4546 4748 494a 4b4c 4d4e 4f50  ABCDEFGHIJKLMNOP\n"
        "00000010: 00ff" "        " "        " "        " "        " "     ..\n";

    start_capture();
    my_showmem(bytes, 0);
    my_showmem(bytes, sizeof(bytes) - 1);
    expect_output(expected, sizeof(expected) - 1);
}

static void run_numbers_tests(void)
{
    RUN_TEST(test_my_swap);
    RUN_TEST(test_my_strlen);
    RUN_TEST(test_my_getnbr);
    RUN_TEST(test_my_getnbr_limits);
    RUN_TEST(test_my_sort_int_array);
    RUN_TEST(test_my_compute_power_rec);
    RUN_TEST(test_my_compute_square_root);
    RUN_TEST(test_my_is_prime);
    RUN_TEST(test_my_find_prime_sup);
}

static void run_strings_tests(void)
{
    RUN_TEST(test_my_strcpy);
    RUN_TEST(test_my_strncpy);
    RUN_TEST(test_my_revstr);
    RUN_TEST(test_my_strstr);
    RUN_TEST(test_my_strcmp);
    RUN_TEST(test_my_strncmp);
    RUN_TEST(test_my_strupcase);
    RUN_TEST(test_my_strlowcase);
    RUN_TEST(test_my_strcapitalize);
    RUN_TEST(test_my_str_isalpha);
    RUN_TEST(test_my_str_isnum);
    RUN_TEST(test_my_str_islower);
    RUN_TEST(test_my_str_isupper);
    RUN_TEST(test_my_str_isprintable);
    RUN_TEST(test_my_strcat);
    RUN_TEST(test_my_strncat);
}

static void run_output_tests(void)
{
    RUN_TEST(test_my_putchar);
    RUN_TEST(test_my_isneg);
    RUN_TEST(test_my_put_nbr);
    RUN_TEST(test_my_putstr);
    RUN_TEST(test_my_showstr);
    RUN_TEST(test_my_showmem);
}

int main(void)
{
    UNITY_BEGIN();
    run_numbers_tests();
    run_strings_tests();
    run_output_tests();
    return UNITY_END();
}
