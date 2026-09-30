/**
 * Checks whether str contains only uppercase alphabetical characters.
 * Returns 1 if str contains only uppercase letters or is empty,
 * otherwise returns 0.
 */
int my_str_isupper(const char *str) {
  int i = 0;

  while (str[i] != '\0') {
    if (!(str[i] >= 'A' && str[i] <= 'Z')) {
      return 0;
    }
    i++;
  }
  return 1;
}
