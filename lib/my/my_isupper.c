/**
** @brief Checks whether a character is an uppercase letter.
**
** @param c The character to check.
**
** @return 1 if the character is an uppercase letter, 0 otherwise.
*/
int my_isupper(int c)
{
    if (c >= 'A' && c <= 'Z') {
        return (1);
    }
    return (0);
}
