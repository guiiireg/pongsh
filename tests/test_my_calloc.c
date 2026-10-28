#include <criterion/criterion.h>
#include <stdlib.h>

#include "my.h"

Test(my_calloc, zeroes_allocated_memory)
{
    char *ptr = my_calloc(5, sizeof(char));

    cr_assert_not_null(ptr);
    for (int i = 0; i < 5; i += 1) {
        cr_assert_eq(ptr[i], 0);
    }
    free(ptr);
}

Test(my_calloc, array_is_usable)
{
    int *array = my_calloc(3, sizeof(int));

    cr_assert_not_null(array);
    array[0] = 1;
    array[2] = 3;
    cr_assert_eq(array[0], 1);
    cr_assert_eq(array[1], 0);
    cr_assert_eq(array[2], 3);
    free(array);
}

Test(my_calloc, invalid_sizes)
{
    cr_assert_null(my_calloc(0, sizeof(char)));
    cr_assert_null(my_calloc(5, 0));
    cr_assert_null(my_calloc(-1, sizeof(char)));
    cr_assert_null(my_calloc(5, -1));
}

Test(my_calloc, multiplication_overflow)
{
    cr_assert_null(my_calloc(2000000000, 2));
}
