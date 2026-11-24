#include "my_ls.h"
#include "my.h"
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void ls_write(char const *text, size_t length)
{
    ssize_t written;

    while (length) {
        written = write(STDOUT_FILENO, text, length);
        if (written < 0 && errno == EINTR)
            continue;
        if (written <= 0) {
            perror("my_ls: write");
            exit(1);
        }
        text += written;
        length -= (size_t)written;
    }
}

void ls_text(char const *text)
{
    ls_write(text, (size_t)my_strlen(text));
}

void ls_spaces(size_t count)
{
    char const spaces[] = "                                ";
    size_t chunk;

    while (count) {
        chunk = sizeof(spaces) - 1;
        if (chunk > count)
            chunk = count;
        ls_write(spaces, chunk);
        count -= chunk;
    }
}

void ls_header(char const *path, int *printed)
{
    if (*printed)
        ls_text("\n");
    ls_text(path);
    ls_text(":\n");
    *printed = 1;
}
