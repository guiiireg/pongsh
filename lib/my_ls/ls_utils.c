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
    if (S_ISDIR(file_stat->st_mode)) {
        my_printf(" %s%s%s\n", COLOR_BLUE, filename, COLOR_RESET);
    } else {
        my_printf(" %s\n", filename);
    }
}

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

void print_file_size(off_t size)
{
    char *size_str;
    int len;
    int padding;
    int i;

    size_str = my_itoa((int)size);
    if (!size_str) {
        my_printf("        ");
        return;
    }
    len = my_strlen(size_str);
    padding = 8 - len;
    for (i = 0; i < padding; i++) {
        my_printf(" ");
    }
    my_printf("%s", size_str);
    my_free(size_str);
}

void print_file_time(time_t mtime)
{
    struct tm *timeinfo;
    const char *months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun",
                           "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    timeinfo = localtime(&mtime);
    if (timeinfo) {
        my_printf(" %s ", months[timeinfo->tm_mon]);
        if (timeinfo->tm_mday < 10) {
            my_printf(" %d ", timeinfo->tm_mday);
        } else {
            my_printf("%d ", timeinfo->tm_mday);
        }
        if (timeinfo->tm_hour < 10) {
            my_printf("0%d:", timeinfo->tm_hour);
        } else {
            my_printf("%d:", timeinfo->tm_hour);
        }
        if (timeinfo->tm_min < 10) {
            my_printf("0%d", timeinfo->tm_min);
        } else {
            my_printf("%d", timeinfo->tm_min);
        }
    } else {
        my_printf(" ??? ?? ??:??");
    }
}

int is_directory(const char *path, const char *filename)
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
        return 0;
    }
    return S_ISDIR(file_stat.st_mode);
}

void print_colored_filename(const char *path, const char *filename)
{
    if (is_directory(path, filename)) {
        my_printf("%s%s%s", COLOR_BLUE, filename, COLOR_RESET);
    } else {
        my_printf("%s", filename);
    }
}
