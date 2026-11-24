#include "pongsh.h"

size_t sh_env_count(char **env)
{
    size_t count = 0;

    while (env[count])
        count++;
    return count;
}

static int has_key(char const *entry, char const *key)
{
    while (*key && *key == *entry) {
        key++;
        entry++;
    }
    return !*key && *entry == '=';
}

size_t sh_env_index(char **env, char const *key)
{
    size_t index = 0;

    while (env[index] && !has_key(env[index], key))
        index++;
    return index;
}

char const *sh_env_get(char **env, char const *key)
{
    size_t index = sh_env_index(env, key);

    if (!env[index])
        return NULL;
    return env[index] + sh_length(key) + 1;
}
