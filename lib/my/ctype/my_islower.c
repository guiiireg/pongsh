/**
** @brief Checks whether a character is a lowercase letter.
**
** @param c The character to check.
**
** @return 1 if the character is a lowercase letter, 0 otherwise.
*/
int my_islower(int c)
{
    if (c >= 'a' && c <= 'z') {
        return (1);
    }
    return (0);
}
