/**
 * ===================================================================
 *                              LS UTILITIES
 * ===================================================================
 * File: ls_utils.c
 * Description: Utility functions for my_ls implementation including
 *              file information display and formatting.
 * Dependencies: my_ls.h
 * ===================================================================
 */

#include "../../include/my_ls.h"

/**
 * @brief Print detailed file information
 * @param file_stat File statistics
 * @param filename Name of the file
 */
void print_detailed_info(const struct stat *file_stat, const char *filename)
{
    struct passwd *pw;
    struct group *gr;

    print_permissions(file_stat->st_mode);
    my_printf(" %d ", (int)file_stat->st_nlink);
    pw = getpwuid(file_stat->st_uid);
    if (pw) {
        my_printf("%s ", pw->pw_name);
    } else {
        my_printf("%d ", file_stat->st_uid);
    }
    gr = getgrgid(file_stat->st_gid);
    if (gr) {
        my_printf("%s ", gr->gr_name);
    } else {
        my_printf("%d ", file_stat->st_gid);
    }
    print_file_size(file_stat->st_size);
    print_file_time(file_stat->st_mtime);
    my_printf(" %s\n", filename);
}

/**
 * @brief Print detailed file information
 * @param filename Name of the file
 * @param path Directory path containing the file
 * @param show_details Whether to show detailed info
 */
void print_file_info(const char *filename, const char *path, int show_details)
{
    struct stat file_stat;
    char full_path[1024];

    if (my_strcmp(path, ".") == 0) {
        my_strcpy(full_path, filename);
    } else {
        my_strcpy(full_path, path);
        my_strcat(full_path, "/");
        my_strcat(full_path, filename);
    }
    if (stat(full_path, &file_stat) == -1) {
        my_printf("?????????? ? ? ? ? ? %s\n", filename);
        return;
    }
    if (show_details) {
        print_detailed_info(&file_stat, filename);
    }
}

/**
 * @brief Print file permissions in rwx format
 * @param mode File mode from stat
 */
void print_permissions(mode_t mode)
{
    if (S_ISDIR(mode))
        my_putchar('d');
    else if (S_ISLNK(mode))
        my_putchar('l');
    else
        my_putchar('-');
    my_putchar((mode & S_IRUSR) ? 'r' : '-');
    my_putchar((mode & S_IWUSR) ? 'w' : '-');
    my_putchar((mode & S_IXUSR) ? 'x' : '-');
    my_putchar((mode & S_IRGRP) ? 'r' : '-');
    my_putchar((mode & S_IWGRP) ? 'w' : '-');
    my_putchar((mode & S_IXGRP) ? 'x' : '-');
    my_putchar((mode & S_IROTH) ? 'r' : '-');
    my_putchar((mode & S_IWOTH) ? 'w' : '-');
    my_putchar((mode & S_IXOTH) ? 'x' : '-');
}

/**
 * @brief Print file size
 * @param size File size in bytes
 */
void print_file_size(off_t size)
{
    my_printf("%8ld", (long)size);
}

/**
 * @brief Print file modification time
 * @param mtime Modification time
 */
void print_file_time(time_t mtime)
{
    struct tm *timeinfo;
    char time_str[20];

    timeinfo = localtime(&mtime);
    if (timeinfo) {
        strftime(time_str, sizeof(time_str), "%b %d %H:%M", timeinfo);
        my_printf(" %s", time_str);
    } else {
        my_printf(" ??? ?? ??:??");
    }
}
