/**
 * Checks whether str contains only alphabetical characters.
 * Returns 1 if str contains only alphabetical characters or is empty,
 * otherwise returns 0.
 */
int my_str_isalpha(const char *str) {
  int i = 0;

  while (str[i] != '\0') {
    if (!((str[i] >= 'a' && str[i] <= 'z') ||
          (str[i] >= 'A' && str[i] <= 'Z'))) {
      return 0;
    }
    i++;
  }
  return 1;
}
