/**
 * @brief Checks whether a value belongs to the ASCII range.
 *
 * @param c The value to check.
 *
 * @return 1 if the value is in the ASCII range (0 to 127), 0 otherwise.
 */
int my_isascii(int c)
{
    if (c >= 0 && c <= 127) {
        return (1);
    }
    return (0);
}
