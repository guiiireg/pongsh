#include "../../include/my.h"

static void print_address(int offset) {
  const char hex_digits[] = "0123456789abcdef";

  for (int i = 7; i >= 0; i--) {
    int shift = i * 4;
    int digit = (offset >> shift) & 0x0F;
    my_putchar(hex_digits[digit]);
  }
  my_putchar(':');
  my_putchar(' ');
}

static void print_hex_byte(unsigned char c) {
  const char hex_digits[] = "0123456789abcdef";

  my_putchar(hex_digits[c / 16]);
  my_putchar(hex_digits[c % 16]);
}

static void print_hex_section(const char *str, int offset, int size) {
  for (int j = 0; j < 16; j++) {
    if (offset + j < size) {
      print_hex_byte((unsigned char)str[offset + j]);
    } else {
      my_putchar(' ');
      my_putchar(' ');
    }
    if (j % 2 == 1) {
      my_putchar(' ');
    }
  }
}

static void print_ascii_section(const char *str, int offset, int size) {
  for (int j = 0; j < 16 && offset + j < size; j++) {
    unsigned char c = (unsigned char)str[offset + j];
    if (c >= 32 && c <= 126) {
      my_putchar((char)c);
    } else {
      my_putchar('.');
    }
  }
}

/**
 * Displays a memory dump of str up to size bytes on the standard output.
 * Each line contains an 8-character hex address, 16 hex bytes in pairs,
 * and the printable ASCII representation.
 * Returns 0.
 */
int my_showmem(const char *str, int size) {
  if (str == 0 || size <= 0)
    return 0;
  for (int offset = 0; offset < size; offset += 16) {
    print_address(offset);
    print_hex_section(str, offset, size);
    print_ascii_section(str, offset, size);
    my_putchar('\n');
  }
  return 0;
}
