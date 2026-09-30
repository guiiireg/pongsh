#ifndef MY_H_
#define MY_H_

void my_putchar(char c);
int my_isneg(int nb);
void my_swap(int *a, int *b);
int my_put_nbr(int nb);
int my_putstr(const char *str);
int my_strlen(const char *str);
int my_getnbr(const char *str);
void my_sort_int_array(int *tab, int size);
int my_compute_power_rec(int nb, int power);
int my_compute_square_root(int nb);
int my_is_prime(int nb);
int my_find_prime_sup(int nb);
char *my_strcpy(char *dest, const char *src);
char *my_strncpy(char *dest, const char *src, int n);
char *my_revstr(char *str);
char *my_strstr(char *str, const char *to_find);
int my_strcmp(const char *s1, const char *s2);
int my_strncmp(const char *s1, const char *s2, int n);
char *my_strupcase(char *str);
int my_str_isalpha(const char *str);
char *my_str_capitalize(char *str);
int my_str_isnum(const char *str);
int my_str_islower(const char *str);
int my_str_isupper(const char *str);
int my_str_isprintable(const char *str);
char *my_strcat(char *dest, const char *str);
char *my_strncat(char *dest, const char *src, int nb);

#endif // MY_H_
