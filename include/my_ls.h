#ifndef MY_LS_H
    #define MY_LS_H

    #include <stddef.h>
    #include <stdint.h>
    #include <sys/stat.h>
    #include <time.h>

typedef struct ls_options {
    int all;
    int long_format;
    int recursive;
    int directory;
    int reverse;
    int by_time;
} ls_options_t;

typedef struct ls_entry {
    char const *name;
    char *path;
    struct stat info;
    struct ls_entry *next;
} ls_entry_t;

int ls_parse_options(int argc, char **argv, ls_options_t *options);
void ls_write(char const *text, size_t length);
void ls_text(char const *text);
void ls_number(uintmax_t value);
void ls_header(char const *path, int *printed);
int ls_display(ls_entry_t const *entry, ls_options_t const *options);
void ls_mode(mode_t mode);
void ls_owner(struct stat const *info);
void ls_date(time_t modified);
int ls_link(ls_entry_t const *entry);
ls_entry_t *ls_create_entry(char const *name, char const *parent, int follow);
void ls_free_entries(ls_entry_t *entry);
ls_entry_t *ls_sort(ls_entry_t *entries, ls_options_t const *options);
int ls_list_directory(char const *path, ls_options_t const *options,
    int header, int *printed);

#endif
