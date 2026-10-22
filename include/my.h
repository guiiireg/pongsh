#ifndef MY_H_
#define MY_H_

#include <stddef.h>

void my_putchar(char c);
int my_putstr(const char *str);
int my_put_nbr(int nb);
int my_strlen(const char *str);
char *my_strcpy(char *dest, const char *src);
char *my_strncpy(char *dest, const char *src, int n);
char *my_revstr(char *str);
int my_strcmp(const char *s1, const char *s2);
int my_strncmp(const char *s1, const char *s2, int n);
char *my_strcat(char *dest, const char *src);
char *my_strncat(char *dest, const char *src, int n);
char *my_strdup(const char *src);
char *my_strndup(const char *src, int n);
char *my_strstr(char *str, const char *to_find);
char *my_strcapitalize(char *str);
void my_swap(int *a, int *b);
char *my_strlowcase(char *str);
char *my_strupcase(char *str);

void *my_memcpy(void *dest, const void *src, size_t size);
void *my_memset(void *ptr, int c, size_t size);
int my_memcmp(const void *s1, const void *s2, size_t size);
void *my_memmove(void *dest, const void *src, size_t size);

#endif /* MY_H_ */
