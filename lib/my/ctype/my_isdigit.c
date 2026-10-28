/**
 * @brief Checks whether a character is a digit.
 *
 * @param c The character to check.
 *
 * @return 1 if the character is a digit, 0 otherwise.
 */
int my_isdigit(int c)
{
    if (c >= '0' && c <= '9') {
        return (1);
    }
    return (0);
}
