#ifndef SHELL_H_
    #define SHELL_H_

    #include <unistd.h>
    #include <stdlib.h>
    #include <stdio.h>

    #define SUCCESS 0
    #define FAILURE 84

void display_prompt(void);
int shell_loop(void);
int is_empty_line(const char *str);

#endif /* !SHELL_H_ */
