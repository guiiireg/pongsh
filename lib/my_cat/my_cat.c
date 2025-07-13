/**
 * ===================================================================
 *                              MY_CAT CORE
 * ===================================================================
 * File: my_cat.c
 * Description: Core implementation of my_cat builtin command that
 *              displays the content of files like Unix cat command.
 * Dependencies: my_cat.h
 * ===================================================================
 */

#include "../../include/my_cat.h"

int my_cat(const char *filename)
{
    if (!filename || my_strlen(filename) == 0) {
        return cat_stdin();
    }
    return cat_file(filename);
}

int cat_file(const char *filename)
{
    int fd;
    int result;

    fd = open_file_for_reading(filename);
    if (fd == -1) {
        return -1;
    }
    result = read_and_output_file(fd, filename);
    close(fd);
    return result;
}

int validate_file(const char *filename)
{
    struct stat file_stat;

    if (!filename) {
        print_cat_error("", "Invalid filename");
        return -1;
    }
    if (stat(filename, &file_stat) == -1) {
        print_cat_error(filename, "No such file or directory");
        return -1;
    }
    if (S_ISDIR(file_stat.st_mode)) {
        print_cat_error(filename, "Is a directory");
        return -1;
    }
    return 0;
}

void print_cat_error(const char *filename, const char *error_msg)
{
    my_printf("%s%s %smy_cat: %s%s%s: %s%s\n",
              ERROR_COLOR, CROSS_MARK, RESET,
              ERROR_COLOR, filename, RESET, error_msg, RESET);
}
