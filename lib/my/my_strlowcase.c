#include "../../include/my.h"

/**
 * Converts all uppercase characters in str to lowercase.
 * Returns the modified string.
 */
char *my_strlowcase(char *str) {
  int i = 0;

  if (str == 0)
    return 0;
  while (str[i] != '\0') {
    if (str[i] >= 'A' && str[i] <= 'Z')
      str[i] += 32;
    i++;
  }
  return str;
}
