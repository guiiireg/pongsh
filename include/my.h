#ifndef MY_H_
# define MY_H_

int my_putchar(char c);
int my_putstr(char const *str);
int my_puterr(char const *str);
int my_isalpha(int c);
int my_isdigit(int c);
int my_isalnum(int c);
int my_isupper(int c);
int my_islower(int c);
int my_isprint(int c);
int my_isascii(int c);
int my_toupper(int c);
int my_tolower(int c);
int my_strlen(char const *str);
char *my_strcpy(char *dest, char const *src);
char *my_strncpy(char *dest, char const *src, int n);
char *my_strcat(char *dest, char const *src);
char *my_strncat(char *dest, char const *src, int n);
char *my_strdup(char const *str);

#endif // MY_H_
