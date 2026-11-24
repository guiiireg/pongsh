#include "my_ls.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define LS_LINK_INITIAL_SIZE 128u

static int show_target(char const *path, char *buffer, size_t capacity)
{
    ssize_t length = readlink(path, buffer, capacity);

    if (length < 0) {
        perror(path);
        return -1;
    }
    if ((size_t)length == capacity)
        return 1;
    ls_text(" -> ");
    ls_write(buffer, (size_t)length);
    return 0;
}

int ls_link(ls_entry_t const *entry)
{
    size_t capacity = LS_LINK_INITIAL_SIZE;
    char *buffer;
    int result;

    while (capacity <= SIZE_MAX / 2) {
        buffer = malloc(capacity);
        if (!buffer) {
            perror("my_ls");
            return 1;
        }
        result = show_target(entry->path, buffer, capacity);
        free(buffer);
        if (result <= 0)
            return result < 0;
        capacity *= 2;
    }
    errno = ENOMEM;
    perror(entry->path);
    return 1;
}
