/**
 * Compares up to n characters of two strings.
 * Returns the difference between the first characters that differ.
 */
int my_strncmp(const char *s1, const char *s2, int n)
{
    int i = 0;

    if (n <= 0)
        return 0;
    while (i < n - 1 && s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i]) {
        i++;
    }
    return (s1[i] - s2[i]);
}
