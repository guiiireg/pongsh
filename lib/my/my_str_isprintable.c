/**
 * Checks whether str contains only printable characters.
 * Returns 1 if str contains only printable characters or is empty,
 * otherwise returns 0.
 */
int my_str_isprintable(const char *str) {
  int i = 0;

  while (str[i] != '\0') {
    if (!(str[i] >= 32 && str[i] <= 126)) {
      return 0;
    }
    i++;
  }
  return 1;
}
