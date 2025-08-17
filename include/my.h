// ============================
//              MY
// ============================
// Made by Guireg on 17/08/2025
// Last update: 17/08/2025
// ============================

#ifndef MY_H_
    #define MY_H_

    #include <unistd.h>
    #include <stdarg.h>
    #include <stdlib.h>
    #include <dirent.h>
    #include <sys/stat.h>
    #include <time.h>
    #include <fcntl.h>

void my_putchar(char c);
int my_put_nbr(int nb);
int my_putstr(char const *str);
int my_strlen(char const *str);
char *my_strcpy(char *dest, char const *src);
int my_strcmp(char const *s1, char const *s2);
int my_str_isalpha(char const *str);
int my_str_isnum(char const *str);
int my_str_islower(char const *str);
int my_str_isupper(char const *str);
int my_str_isprintable(char const *str);
char *my_strupcase(char *str);
char *my_strlowcase(char *str);
char *my_strcapitalize(char *str);
int my_printf(char const *format, ...);
int handle_char(va_list args);
int handle_string(va_list args);
int handle_integer(va_list args);
int handle_percent(void);
int process_format(char format, va_list args);
int my_ls(char const *path);
int list_directory(char const *path);
int display_file_info(char const *path, char const *name);
int build_full_path(char *dest, char const *dir, char const *file);
int copy_string_to_dest(char *dest, char const *src, int start_pos);
int add_separator_if_needed(char *dest, char const *dir, int pos);
int my_cat(char const *path);
int cat_file(char const *path);
int cat_directory(char const *path);
int check_file_type(char const *path);

#endif /* !MY_H_ */
