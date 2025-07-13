/**
 * ===================================================================
 *                              MY_CAT IO OPERATIONS
 * ===================================================================
 * File: cat_io.c
 * Description: Input/output operations for my_cat command.
 * Dependencies: my_cat.h
 * ===================================================================
 */

#include "../../include/my_cat.h"

int open_file_for_reading(const char *filename)
{
    int fd;

    if (validate_file(filename) != 0) {
        return -1;
    }
    fd = open(filename, O_RDONLY);
    if (fd == -1) {
        print_cat_error(filename, "Permission denied");
        return -1;
    }
    return fd;
}

int read_and_output_file(int fd, const char *filename)
{
    char buffer[CAT_BUFFER_SIZE];
    ssize_t bytes_read;

    while ((bytes_read = read(fd, buffer, CAT_BUFFER_SIZE)) > 0) {
        write(1, buffer, bytes_read);
    }
    if (bytes_read == -1) {
        print_cat_error(filename, "Error reading file");
        return -1;
    }
    return 0;
}

int cat_stdin(void)
{
    char buffer[CAT_BUFFER_SIZE];
    ssize_t bytes_read;

    while ((bytes_read = read(0, buffer, CAT_BUFFER_SIZE)) > 0) {
        write(1, buffer, bytes_read);
    }
    if (bytes_read == -1) {
        print_cat_error("stdin", "Error reading from stdin");
        return -1;
    }
    return 0;
}
