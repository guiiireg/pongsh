/**
 * @brief Converts a lowercase letter to uppercase.
 *
 * @param c The character to convert.
 *
 * @return The uppercase equivalent, or the character unchanged.
 */
int my_toupper(int c)
{
    if (c >= 'a' && c <= 'z') {
        return (c - 32);
    }
    return (c);
}
