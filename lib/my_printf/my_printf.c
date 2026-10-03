#include "../../include/my.h"
#include "../../include/my_printf.h"

/**
 * Traverses format and prints literal characters and escaped percent symbols.
 * Returns the total number of characters printed, or -1 if format is NULL.
 */
int my_printf(const char *format, ...) {
  int i = 0;
  int count = 0;

  if (format == 0)
    return -1;
  while (format[i] != '\0') {
    if (format[i] == '%' && format[i + 1] == '%')
      i++;
    else if (format[i] == '%' && format[i + 1] == '\0') {
      i++;
      continue;
    }
    my_putchar(format[i]);
    count++;
    i++;
  }
  return count;
}
