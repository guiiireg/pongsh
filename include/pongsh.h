#ifndef PONGSH_H
    #define PONGSH_H

    #include <stddef.h>

    #define SH_INITIAL_CWD 128u
    #define SH_STATUS_MASK 255u
    #define SH_CANNOT_EXECUTE 126
    #define SH_NOT_FOUND 127
    #define SH_SIGNAL_STATUS 128
    #define SH_INITIAL_LINE 128u

typedef struct shell_s {
    char **env;
    int status;
    int running;
    int interactive;
} shell_t;

typedef struct shell_parser_s {
    char *cursor;
    char **args;
} shell_parser_t;

size_t sh_length(char const *text);
void sh_write(int fd, char const *text);
void sh_error(char const *subject, char const *message);
void sh_interrupt(int sig);
int sh_read_line(char **line);
int sh_parse_next(shell_parser_t *parser);
int sh_execute(shell_t *shell, char **args);
int sh_external(shell_t *shell, char **args);
void sh_exec_path(char **args, char **env);
char **sh_env_copy(char **source);
void sh_env_free(char **env);
char const *sh_env_get(char **env, char const *key);
int sh_env_set(shell_t *shell, char const *key, char const *value);
void sh_env_remove(shell_t *shell, char const *key);
size_t sh_env_index(char **env, char const *key);
size_t sh_env_count(char **env);
int sh_cd(shell_t *shell, char **args);
int sh_setenv(shell_t *shell, char **args);
int sh_unsetenv(shell_t *shell, char **args);
int sh_exit(shell_t *shell, char **args);

#endif
