#include "../../include/my.h"

static void print_non_printable(unsigned char c) {
  const char hex_digits[] = "0123456789abcdef";

  my_putchar('\\');
  my_putchar(hex_digits[c / 16]);
  my_putchar(hex_digits[c % 16]);
}

/**
 * Displays a string on the standard output.
 * Non-printable characters are printed as a backslash followed by their
 * ASCII value in lowercase hexadecimal (two digits).
 * Returns 0.
 */
int my_showstr(const char *str) {
  int i = 0;

  if (str == 0)
    return 0;
  while (str[i] != '\0') {
    if (str[i] >= 32 && str[i] <= 126) {
      my_putchar(str[i]);
    } else {
      print_non_printable((unsigned char)str[i]);
    }
    i++;
  }
  return 0;
}
