/**
 * Checks whether str contains only numeric characters.
 * Returns 1 if str contains only digits or is empty,
 * otherwise returns 0.
 */
int my_str_isnum(const char *str) {
  int i = 0;

  while (str[i] != '\0') {
    if (!(str[i] >= '0' && str[i] <= '9')) {
      return 0;
    }
    i++;
  }
  return 1;
}
