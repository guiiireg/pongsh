#include <stddef.h>

static void swap_bytes(char *a, char *b, int size)
{
    int i = 0;
    char tmp;

    while (i < size) {
        tmp = a[i];
        a[i] = b[i];
        b[i] = tmp;
        i += 1;
    }
}

/**
 * @brief Sorts an array using a comparison callback.
 *
 * The comparison function receives pointers to two elements and must
 * return a negative value, 0, or a positive value.
 *
 * @param base The array to sort.
 * @param nmemb The number of elements in the array.
 * @param size The size of each element, in bytes.
 * @param cmp The comparison function.
 */
void my_sort(void *base, int nmemb, int size,
    int (*cmp)(void const *, void const *))
{
    char *bytes = base;
    int i = 1;

    if (base == NULL || cmp == NULL || nmemb < 1 || size < 1) {
        return;
    }
    while (i < nmemb) {
        int j = i;

        while (j > 0 && cmp(&bytes[(j - 1) * size], &bytes[j * size]) > 0) {
            swap_bytes(&bytes[(j - 1) * size], &bytes[j * size], size);
            j -= 1;
        }
        i += 1;
    }
}
