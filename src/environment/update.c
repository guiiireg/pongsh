#include "pongsh.h"
#include <stdint.h>
#include <stdlib.h>

static char *make_entry(char const *key, char const *value)
{
    size_t left = sh_length(key);
    size_t right = sh_length(value);
    char *entry;
    size_t index;

    if (right > SIZE_MAX - 2 || left > SIZE_MAX - right - 2)
        return NULL;
    entry = malloc(left + right + 2);
    if (!entry)
        return NULL;
    for (index = 0; index < left; index++)
        entry[index] = key[index];
    entry[left] = '=';
    for (index = 0; index <= right; index++)
        entry[left + 1 + index] = value[index];
    return entry;
}

static int insert_entry(shell_t *shell, char *entry, size_t count)
{
    char **env;
    size_t index;

    if (count >= SIZE_MAX / sizeof(*env) - 1)
        return -1;
    env = malloc((count + 2) * sizeof(*env));
    if (!env)
        return -1;
    for (index = 0; index < count; index++)
        env[index] = shell->env[index];
    env[count] = entry;
    env[count + 1] = NULL;
    free(shell->env);
    shell->env = env;
    return 0;
}

int sh_env_set(shell_t *shell, char const *key, char const *value)
{
    size_t index = sh_env_index(shell->env, key);
    char *entry = make_entry(key, value);

    if (!entry)
        return -1;
    if (shell->env[index]) {
        free(shell->env[index]);
        shell->env[index] = entry;
        return 0;
    }
    if (insert_entry(shell, entry, index) == 0)
        return 0;
    free(entry);
    return -1;
}

void sh_env_remove(shell_t *shell, char const *key)
{
    size_t index = sh_env_index(shell->env, key);

    if (!shell->env[index])
        return;
    free(shell->env[index]);
    do {
        shell->env[index] = shell->env[index + 1];
        index++;
    } while (shell->env[index - 1]);
}
