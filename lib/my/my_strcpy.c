/**
 * Copies the source string into the destination string.
 * Returns the destination string.
 */
char *my_strcpy(char *dest, const char *src) {
  int i = 0;

  while (src[i] != '\0') {
    dest[i] = src[i];
    i++;
  }
  dest[i] = '\0';
  return dest;
}
