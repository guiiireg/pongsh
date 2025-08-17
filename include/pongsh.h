// ============================
//           PONGSH
// ============================
// Made by Guireg on 17/08/2025
// Last update: 17/08/2025
// ============================

#ifndef PONGSH_H_
    #define PONGSH_H_

    #include "my.h"
    #include <sys/wait.h>
    #include <stdio.h>

    #define MAX_INPUT_SIZE 1024
    #define MAX_ARGS 64
    #define PROMPT "pongsh> "

typedef struct {
    char *name;
    int (*func)(char **args);
} builtin_t;

int pongsh_main(void);
int shell_loop(void);
char *read_line(void);
char **parse_line(char *line);
int execute_command(char **args);
int is_builtin(char *command);
int call_builtin(char **args);
void free_args(char **args);
int pongsh_exit(char **args);
int pongsh_ls(char **args);
int pongsh_cat(char **args);
int pongsh_help(char **args);
int pongsh_cd(char **args);
int pongsh_pwd(char **args);

#endif /* !PONGSH_H_ */
