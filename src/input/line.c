#include "pongsh.h"
#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static int grow_line(char **line, size_t *capacity, size_t used)
{
    char *next;
    size_t index;

    if (*capacity > SIZE_MAX / 2)
        return -1;
    next = malloc(*capacity * 2);
    if (!next)
        return -1;
    for (index = 0; index < used; index++)
        next[index] = (*line)[index];
    free(*line);
    *line = next;
    *capacity *= 2;
    return 0;
}

static int read_byte(char *byte)
{
    ssize_t result;

    do {
        result = read(STDIN_FILENO, byte, 1);
    } while (result < 0 && errno == EINTR);
    if (result < 0)
        perror("pongsh: read");
    return (int)result;
}

static int append_byte(char **line, size_t *capacity, size_t used, char byte)
{
    if (!byte) {
        sh_error("pongsh", "NUL byte in input");
        return -1;
    }
    if (used + 1 == *capacity && grow_line(line, capacity, used) < 0) {
        sh_error("pongsh", "out of memory");
        return -1;
    }
    (*line)[used] = byte;
    return 0;
}

static int fill_line(char **line, size_t *capacity)
{
    size_t used = 0;
    char byte;
    int result = read_byte(&byte);

    while (result > 0 && byte != '\n') {
        if (append_byte(line, capacity, used, byte) < 0)
            return -1;
        used++;
        result = read_byte(&byte);
    }
    (*line)[used] = '\0';
    if (result < 0)
        return -1;
    return result || used;
}

int sh_read_line(char **line)
{
    size_t capacity = SH_INITIAL_LINE;
    int result;

    *line = malloc(capacity);
    if (!*line) {
        sh_error("pongsh", "out of memory");
        return -1;
    }
    result = fill_line(line, &capacity);
    if (result <= 0) {
        free(*line);
        *line = NULL;
    }
    return result;
}
