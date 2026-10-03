#include "../../include/my.h"

/**
 * Checks whether c is an alphanumeric character.
 * Returns 1 if c is alphanumeric, otherwise returns 0.
 */
static int is_alphanumeric(char c) {
  if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
      (c >= '0' && c <= '9')) {
    return 1;
  }
  return 0;
}

/**
 * Capitalizes the first letter of each word in a string.
 * Converts any subsequent letters of each word to lowercase.
 * Returns the modified string.
 */
char *my_strcapitalize(char *str) {
  int i = 0;

  if (str == 0)
    return 0;
  while (str[i] != '\0') {
    if (str[i] >= 'a' && str[i] <= 'z') {
      if (i == 0 || !is_alphanumeric(str[i - 1]))
        str[i] -= 32;
    } else if (str[i] >= 'A' && str[i] <= 'Z') {
      if (i > 0 && is_alphanumeric(str[i - 1]))
        str[i] += 32;
    }
    i++;
  }
  return str;
}
