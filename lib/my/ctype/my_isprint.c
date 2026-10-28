/**
 * @brief Checks whether a character is printable.
 *
 * @param c The character to check.
 *
 * @return 1 if the character is printable, 0 otherwise.
 */
int my_isprint(int c)
{
    if (c >= 32 && c <= 126) {
        return (1);
    }
    return (0);
}
