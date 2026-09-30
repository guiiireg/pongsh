/**
 * Concatenates two strings by appending src to dest.
 * Returns a pointer to the destination string dest.
 */
char *my_strcat(char *dest, const char *src) {
  int i = 0;
  int j = 0;

  while (dest[i] != '\0') {
    i++;
  }
  while (src[j] != '\0') {
    dest[i + j] = src[j];
    j++;
  }
  dest[i + j] = '\0';
  return dest;
}
