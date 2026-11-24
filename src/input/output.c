#include "pongsh.h"
#include <errno.h>
#include <unistd.h>

size_t sh_length(char const *text)
{
    size_t length = 0;

    while (text[length])
        length++;
    return length;
}

void sh_write(int fd, char const *text)
{
    size_t length = sh_length(text);
    ssize_t written;

    while (length) {
        written = write(fd, text, length);
        if (written < 0 && errno == EINTR)
            continue;
        if (written <= 0)
            return;
        text += written;
        length -= (size_t)written;
    }
}

void sh_error(char const *subject, char const *message)
{
    sh_write(STDERR_FILENO, subject);
    sh_write(STDERR_FILENO, ": ");
    sh_write(STDERR_FILENO, message);
    sh_write(STDERR_FILENO, "\n");
}

void sh_interrupt(int sig)
{
    char const prompt[] = "\npongsh$ ";
    int previous = errno;

    (void)sig;
    (void)write(STDOUT_FILENO, prompt, sizeof(prompt) - 1);
    errno = previous;
}
