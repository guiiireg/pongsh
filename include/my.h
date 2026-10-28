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
int my_strcmp(char const *s1, char const *s2);
int my_strncmp(char const *s1, char const *s2, int n);
char *my_strchr(char const *str, int c);
char *my_strrchr(char const *str, int c);
char *my_strstr(char const *str, char const *needle);
int my_revstr(char *str);
void *my_memset(void *s, int c, int n);
int my_bzero(void *s, int n);
void *my_memcpy(void *dest, void const *src, int n);
void *my_memmove(void *dest, void const *src, int n);
void *my_memchr(void const *s, int c, int n);
int my_memcmp(void const *s1, void const *s2, int n);
void *my_calloc(int nmemb, int size);

#endif // MY_H_
