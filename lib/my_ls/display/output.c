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

void ls_number(uintmax_t value)
{
    char buffer[sizeof(value) * CHAR_BIT];
    char *end = buffer + sizeof(buffer);
    char *digit = end;

    do {
        digit--;
        *digit = '0' + value % 10;
        value /= 10;
    } while (value);
    ls_write(digit, (size_t)(end - digit));
}

void ls_header(char const *path, int *printed)
{
    if (*printed)
        ls_text("\n");
    ls_text(path);
    ls_text(":\n");
    *printed = 1;
}
