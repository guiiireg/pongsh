/**
 * @brief Converts an uppercase letter to lowercase.
 *
 * @param c The character to convert.
 *
 * @return The lowercase equivalent, or the character unchanged.
 */
int my_tolower(int c)
{
    if (c >= 'A' && c <= 'Z') {
        return (c + 32);
    }
    return (c);
}
