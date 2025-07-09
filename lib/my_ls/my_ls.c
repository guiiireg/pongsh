/**
 * ===================================================================
 *                              MY_LS CORE
 * ===================================================================
 * File: my_ls.c
 * Description: Core implementation of my_ls builtin command with
 *              basic functionality similar to Unix ls command.
 * Dependencies: my_ls.h
 * ===================================================================
 */

#include "../../include/my_ls.h"

static DIR *open_directory(const char *dir_path);

/**
 * @brief Simple ls implementation without flags
 * @param path Directory path to list (NULL for current directory)
 * @return 0 on success, -1 on error
 */
int my_ls(const char *path)
{
    DIR *dir;
    const char *dir_path = path ? path : ".";

    dir = open_directory(dir_path);
    if (!dir) {
        return -1;
    }
    process_directory_entries(dir, dir_path, 0, 0);
    closedir(dir);
    return 0;
}

/**
 * @brief Parse ls flags
 * @param flags String containing flags
 * @param show_hidden Pointer to hidden flag
 * @param show_details Pointer to details flag
 */
void parse_ls_flags(const char *flags, int *show_hidden, int *show_details)
{
    int i = 0;

    if (!flags) {
        return;
    }

    while (flags[i]) {
        switch (flags[i]) {
            case 'a':
                *show_hidden = 1;
                break;
            case 'l':
                *show_details = 1;
                break;
        }
        i++;
    }
}

/**
 * @brief Compare two strings for sorting
 * @param a First string
 * @param b Second string
 * @return Comparison result
 */
static int compare_strings(const char *a, const char *b)
{
    return my_strcmp(a, b);
}

/**
 * @brief Sort array of strings using simple bubble sort
 * @param entries Array of string pointers
 * @param count Number of entries
 */
static void sort_entries(char **entries, int count)
{
    int i;
    int j;
    char *temp;

    for (i = 0; i < count - 1; i++) {
        for (j = i + 1; j < count; j++) {
            if (compare_strings(entries[i], entries[j]) <= 0) {
                continue;
            }
            temp = entries[i];
            entries[i] = entries[j];
            entries[j] = temp;
        }
    }
}

/**
 * @brief Read directory entries into array
 * @param dir Directory pointer
 * @param entries Array to store entries
 * @param show_hidden Show hidden files flag
 * @return Number of entries read
 */
static int read_directory_entries(DIR *dir, char **entries, int show_hidden)
{
    struct dirent *entry;
    int count = 0;

    while ((entry = readdir(dir)) != NULL && count < 1024) {
        if (!show_hidden && entry->d_name[0] == '.') {
            continue;
        }
        entries[count] = my_strdup(entry->d_name);
        if (!entries[count]) {
            break;
        }
        count++;
    }
    return count;
}

/**
 * @brief Free entries array
 * @param entries Array of entries
 * @param count Number of entries
 */
static void free_entries(char **entries, int count)
{
    int i;

    for (i = 0; i < count; i++) {
        my_free(entries[i]);
    }
}

/**
 * @brief Display directory entries
 * @param entries Array of entries
 * @param count Number of entries
 * @param dir_path Directory path
 * @param show_details Show detailed info flag
 */
static void display_entries(char **entries, int count, const char *dir_path,
                           int show_details)
{
    int i;

    for (i = 0; i < count; i++) {
        if (show_details) {
            print_file_info(entries[i], dir_path, 1);
        } else {
            my_printf("%s  ", entries[i]);
        }
    }
    if (!show_details) {
        my_printf("\n");
    }
    free_entries(entries, count);
}

/**
 * @brief Process directory entries
 * @param dir Directory pointer
 * @param dir_path Directory path
 * @param show_hidden Show hidden files flag
 * @param show_details Show detailed info flag
 */
void process_directory_entries(DIR *dir, const char *dir_path,
                              int show_hidden, int show_details)
{
    char *entries[1024];
    int count;

    count = read_directory_entries(dir, entries, show_hidden);
    sort_entries(entries, count);
    display_entries(entries, count, dir_path, show_details);
}

/**
 * @brief Open directory with error handling
 * @param dir_path Directory path
 * @return DIR pointer or NULL on error
 */
static DIR *open_directory(const char *dir_path)
{
    DIR *dir = opendir(dir_path);

    if (!dir) {
        my_printf("my_ls: cannot access '%s': No such file or directory\n",
                  dir_path);
    }
    return dir;
}

/**
 * @brief ls implementation with flags support
 * @param path Directory path to list
 * @param flags String containing flags (e.g., "la")
 * @return 0 on success, -1 on error
 */
int my_ls_with_flags(const char *path, const char *flags)
{
    DIR *dir;
    const char *dir_path = path ? path : ".";
    int show_hidden = 0;
    int show_details = 0;

    parse_ls_flags(flags, &show_hidden, &show_details);
    dir = open_directory(dir_path);
    if (!dir) {
        return -1;
    }
    process_directory_entries(dir, dir_path, show_hidden, show_details);
    closedir(dir);
    return 0;
}
