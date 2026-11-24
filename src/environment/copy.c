#include "pongsh.h"
#include <stdint.h>
#include <stdlib.h>

static char *copy_text(char const *text)
{
    size_t length = sh_length(text);
    char *copy = malloc(length + 1);
    size_t index;

    if (!copy)
        return NULL;
    for (index = 0; index <= length; index++)
        copy[index] = text[index];
    return copy;
}

char **sh_env_copy(char **source)
{
    size_t count = sh_env_count(source);
    char **env;
    size_t index;

    if (count >= SIZE_MAX / sizeof(*env))
        return NULL;
    env = malloc((count + 1) * sizeof(*env));
    if (!env)
        return NULL;
    for (index = 0; index < count; index++) {
        env[index] = copy_text(source[index]);
        if (!env[index]) {
            sh_env_free(env);
            return NULL;
        }
    }
    env[count] = NULL;
    return env;
}

void sh_env_free(char **env)
{
    size_t index = 0;

    while (env[index]) {
        free(env[index]);
        index++;
    }
    free(env);
}
