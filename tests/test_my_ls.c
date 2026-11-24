#include "my_ls.h"
#include "unity.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static ls_entry_t *owned_entry;
static char fixture_dir[] = "/tmp/pongsh-ls-test-XXXXXX";
static char fixture_link[sizeof(fixture_dir) + sizeof("/link")];
static int fixture_created;
static int link_created;

void setUp(void)
{
}

void tearDown(void)
{
    ls_free_entries(owned_entry);
    owned_entry = NULL;
    if (link_created)
        unlink(fixture_link);
    if (fixture_created)
        rmdir(fixture_dir);
    link_created = 0;
    fixture_created = 0;
}

static void test_ls_parse_options_grouped(void)
{
    char *argv[] = {"my_ls", "-alRdrt", NULL};
    ls_options_t options = {0};

    TEST_ASSERT_EQUAL_INT(0, ls_parse_options(2, argv, &options));
    TEST_ASSERT_TRUE(options.all);
    TEST_ASSERT_TRUE(options.long_format);
    TEST_ASSERT_TRUE(options.recursive);
    TEST_ASSERT_TRUE(options.directory);
    TEST_ASSERT_TRUE(options.reverse);
    TEST_ASSERT_TRUE(options.by_time);
}

static void test_ls_parse_options_compacts_operands(void)
{
    char *argv[] = {"my_ls", "one", "-t", "two", "-a", "-", NULL};
    ls_options_t options = {0};

    TEST_ASSERT_EQUAL_INT(3, ls_parse_options(6, argv, &options));
    TEST_ASSERT_EQUAL_STRING("one", argv[1]);
    TEST_ASSERT_EQUAL_STRING("two", argv[2]);
    TEST_ASSERT_EQUAL_STRING("-", argv[3]);
    TEST_ASSERT_TRUE(options.all);
    TEST_ASSERT_TRUE(options.by_time);
    TEST_ASSERT_FALSE(options.reverse);
}

static void test_ls_parse_options_stops_at_double_dash(void)
{
    char *argv[] = {"my_ls", "-r", "--", "-a", "--", NULL};
    ls_options_t options = {0};

    TEST_ASSERT_EQUAL_INT(2, ls_parse_options(5, argv, &options));
    TEST_ASSERT_EQUAL_STRING("-a", argv[1]);
    TEST_ASSERT_EQUAL_STRING("--", argv[2]);
    TEST_ASSERT_TRUE(options.reverse);
    TEST_ASSERT_FALSE(options.all);
}

static void test_ls_parse_options_rejects_unknown_flag(void)
{
    char *argv[] = {"my_ls", "-q", NULL};
    ls_options_t options = {0};

    TEST_ASSERT_EQUAL_INT(-1, ls_parse_options(2, argv, &options));
}

static void assert_order(ls_entry_t const *entry, ls_entry_t *const *expected,
    size_t count)
{
    for (size_t index = 0; index < count; index++) {
        TEST_ASSERT_EQUAL_PTR(expected[index], entry);
        entry = entry->next;
    }
    TEST_ASSERT_NULL(entry);
}

static void test_ls_sort_empty_and_single(void)
{
    ls_options_t options = {0};
    ls_entry_t entry = {.name = "only"};

    TEST_ASSERT_NULL(ls_sort(NULL, &options));
    TEST_ASSERT_EQUAL_PTR(&entry, ls_sort(&entry, &options));
    TEST_ASSERT_NULL(entry.next);
}

static void test_ls_sort_names_and_reverse(void)
{
    ls_options_t options = {0};
    ls_entry_t b = {.name = "b"};
    ls_entry_t a = {.name = "a", .next = &b};
    ls_entry_t c = {.name = "c", .next = &a};
    ls_entry_t *ascending[] = {&a, &b, &c};
    ls_entry_t *descending[] = {&c, &b, &a};
    ls_entry_t *head = ls_sort(&c, &options);

    assert_order(head, ascending, 3);
    options.reverse = 1;
    assert_order(ls_sort(head, &options), descending, 3);
}

static void test_ls_sort_time_uses_nanoseconds_and_names(void)
{
    ls_options_t options = {.by_time = 1};
    ls_entry_t b = {.name = "b", .info.st_mtim = {2, 100}};
    ls_entry_t a = {.name = "a", .info.st_mtim = {2, 100}, .next = &b};
    ls_entry_t c = {.name = "c", .info.st_mtim = {2, 200}, .next = &a};
    ls_entry_t d = {.name = "d", .info.st_mtim = {1, 999}, .next = &c};
    ls_entry_t *newest[] = {&c, &a, &b, &d};
    ls_entry_t *oldest[] = {&d, &b, &a, &c};
    ls_entry_t *head = ls_sort(&d, &options);

    assert_order(head, newest, 4);
    options.reverse = 1;
    assert_order(ls_sort(head, &options), oldest, 4);
}

static void test_ls_create_entry_joins_parent_and_name(void)
{
    owned_entry = ls_create_entry(".", ".", 0);
    TEST_ASSERT_NOT_NULL(owned_entry);
    TEST_ASSERT_EQUAL_STRING("./.", owned_entry->path);
    TEST_ASSERT_EQUAL_STRING(".", owned_entry->name);
    TEST_ASSERT_TRUE(S_ISDIR(owned_entry->info.st_mode));
    TEST_ASSERT_NULL(owned_entry->next);
}

static void test_ls_create_entry_handles_parent_with_slash(void)
{
    owned_entry = ls_create_entry(".", "./", 0);
    TEST_ASSERT_NOT_NULL(owned_entry);
    TEST_ASSERT_EQUAL_STRING("./.", owned_entry->path);
    TEST_ASSERT_EQUAL_STRING(".", owned_entry->name);
}

static void test_ls_create_entry_follows_directory_link_on_request(void)
{
    TEST_ASSERT_NOT_NULL(mkdtemp(fixture_dir));
    fixture_created = 1;
    snprintf(fixture_link, sizeof(fixture_link), "%s/link", fixture_dir);
    TEST_ASSERT_EQUAL_INT(0, symlink(".", fixture_link));
    link_created = 1;
    owned_entry = ls_create_entry("link", fixture_dir, 0);
    TEST_ASSERT_NOT_NULL(owned_entry);
    TEST_ASSERT_TRUE(S_ISLNK(owned_entry->info.st_mode));
    ls_free_entries(owned_entry);
    owned_entry = ls_create_entry("link", fixture_dir, 1);
    TEST_ASSERT_NOT_NULL(owned_entry);
    TEST_ASSERT_TRUE(S_ISDIR(owned_entry->info.st_mode));
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_ls_parse_options_grouped);
    RUN_TEST(test_ls_parse_options_compacts_operands);
    RUN_TEST(test_ls_parse_options_stops_at_double_dash);
    RUN_TEST(test_ls_parse_options_rejects_unknown_flag);
    RUN_TEST(test_ls_sort_empty_and_single);
    RUN_TEST(test_ls_sort_names_and_reverse);
    RUN_TEST(test_ls_sort_time_uses_nanoseconds_and_names);
    RUN_TEST(test_ls_create_entry_joins_parent_and_name);
    RUN_TEST(test_ls_create_entry_handles_parent_with_slash);
    RUN_TEST(test_ls_create_entry_follows_directory_link_on_request);
    return UNITY_END();
}
