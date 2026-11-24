#include "pongsh.h"
#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static char *candidate(char const *dir, size_t length, char const *name)
{
    size_t count = sh_length(name);
    size_t index;
    size_t j;
    char *path;

    if (count > SIZE_MAX - 2 || length > SIZE_MAX - count - 2)
        return NULL;
    path = malloc(length + count + 2);
    if (!path)
        return NULL;
    for (index = 0; index < length; index++)
        path[index] = dir[index];
    if (index) {
        path[index] = '/';
        index++;
    }
    for (j = 0; j <= count; j++)
        path[index + j] = name[j];
    return path;
}

static int try_directory(char const *dir, size_t length, char **args,
    char **env)
{
    char *path = candidate(dir, length, args[0]);
    int error;

    if (!path) {
        sh_error("pongsh", "out of memory");
        exit(1);
    }
    execve(path, args, env);
    error = errno;
    free(path);
    if (error != EACCES && error != ENOENT && error != ENOTDIR) {
        errno = error;
        perror(args[0]);
        exit(SH_CANNOT_EXECUTE);
    }
    return error == EACCES;
}

static int search_path(char const *path, char **args, char **env)
{
    size_t length;
    int denied = 0;

    if (!path)
        path = "/bin:/usr/bin";
    while (1) {
        length = 0;
        while (path[length] && path[length] != ':')
            length++;
        denied |= try_directory(path, length, args, env);
        if (!path[length])
            return denied;
        path += length + 1;
    }
}

static int is_explicit(char const *command)
{
    while (*command) {
        if (*command == '/')
            return 1;
        command++;
    }
    return 0;
}

void sh_exec_path(char **args, char **env)
{
    int error;

    if (is_explicit(args[0])) {
        execve(args[0], args, env);
        error = errno;
        perror(args[0]);
        if (error == ENOENT || error == ENOTDIR)
            exit(SH_NOT_FOUND);
        exit(SH_CANNOT_EXECUTE);
    }
    if (*args[0] && search_path(sh_env_get(env, "PATH"), args, env)) {
        sh_error(args[0], "permission denied");
        exit(SH_CANNOT_EXECUTE);
    }
    sh_error(args[0], "command not found");
    exit(SH_NOT_FOUND);
}
