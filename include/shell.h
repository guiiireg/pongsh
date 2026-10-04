#ifndef SHELL_H_
    #define SHELL_H_

    #include <unistd.h>
    #include <stdlib.h>
    #include <stdio.h>
    #include <sys/types.h>
    #include <sys/wait.h>

    #define SUCCESS 0
    #define FAILURE 84

    #define IS_DELIM(c) ((c) == ' ' || (c) == '\t')

void display_prompt(void);
int shell_loop(void);
int is_empty_line(const char *str);
char **split_words(const char *str);
void free_word_array(char **array);
int exec_command(char **argv);

#endif /* !SHELL_H_ */
