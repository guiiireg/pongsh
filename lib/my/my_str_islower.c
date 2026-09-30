/**
 * Checks whether str contains only lowercase alphabetical characters.
 * Returns 1 if str contains only lowercase letters or is empty,
 * otherwise returns 0.
 */
int my_str_islower(const char *str) {
  int i = 0;

  while (str[i] != '\0') {
    if (!(str[i] >= 'a' && str[i] <= 'z')) {
      return 0;
    }
    i++;
  }
  return 1;
}
