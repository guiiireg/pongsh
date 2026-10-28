/**
** @brief Checks whether a character is alphabetic.
**
** @param c The character to check.
**
** @return 1 if the character is alphabetic, 0 otherwise.
*/
int my_isalpha(int c)
{
    if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
        return (1);
    }
    return (0);
}
