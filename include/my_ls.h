#ifndef MY_LS_H
    #define MY_LS_H

    #include <limits.h>
    #include <stddef.h>
    #include <stdint.h>
    #include <sys/stat.h>
    #include <time.h>

    #define LS_HALF_YEAR 15778476u
    #define LS_LINK_INITIAL_SIZE 128u
    #define LS_SIZE_BUFFER (sizeof(uintmax_t) * CHAR_BIT + 4)
    #define LS_SIZE_BASE 1000u

typedef struct ls_options_s {
    int all;
    int long_format;
    int recursive;
    int directory;
    int reverse;
    int by_time;
} ls_options_t;

typedef struct ls_entry_s {
    char const *name;
    char *path;
    struct stat info;
    struct ls_entry_s *next;
} ls_entry_t;

typedef struct ls_columns_s {
    size_t size;
    size_t owner;
} ls_columns_t;

int ls_parse_options(int argc, char **argv, ls_options_t *options);
void ls_write(char const *text, size_t length);
void ls_text(char const *text);
size_t ls_decimal(char *text, uintmax_t value);
void ls_spaces(size_t count);
void ls_header(char const *path, int *printed);
int ls_display(ls_entry_t const *entry, ls_options_t const *options,
    ls_columns_t const *columns);
void ls_measure(ls_columns_t *columns, ls_entry_t const *entries,
    int skip_directories);
void ls_size(char *text, struct stat const *info);
char const *ls_owner(uid_t uid, char *fallback);
char const *ls_icon(ls_entry_t const *entry);
void ls_mode(mode_t mode);
void ls_date(time_t modified);
int ls_link(ls_entry_t const *entry);
ls_entry_t *ls_create_entry(char const *name, char const *parent, int follow);
void ls_free_entries(ls_entry_t *entry);
ls_entry_t *ls_sort(ls_entry_t *entries, ls_options_t const *options);
int ls_list_directory(char const *path, ls_options_t const *options,
    int header, int *printed);

#endif
