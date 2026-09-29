/**
 * Copies up to n characters from the source string into the destination.
 * Fills the remaining space with null characters if needed.
 * Returns the destination string.
 */
char *my_strncpy(char *dest, const char *src, int n)
{
    int i = 0;

    while (i < n && src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    while (i < n) {
        dest[i] = '\0';
        i++;
    }
    return dest;
}
