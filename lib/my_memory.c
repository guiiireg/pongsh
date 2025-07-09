/**
 * ============================================================================
 *                          MEMORY MANAGEMENT LIBRARY
 * ============================================================================
 * File: my_memory.c
 * Description: This file contains memory management functions including
 *              allocation, deallocation, and memory manipulation operations.
 * Dependencies: stdlib.h (for malloc/free), pongsh.h
 * ============================================================================
 */

#include "../include/pongsh.h"

void *my_malloc(size_t size)
{
    void *ptr = malloc(size);

    if (ptr)
        my_memset(ptr, 0, size);
    return ptr;
}

void my_free(void *ptr)
{
    if (ptr)
        free(ptr);
}

void *my_memset(void *ptr, int value, size_t num)
{
    unsigned char *byte_ptr = (unsigned char *)ptr;
    size_t i = 0;

    while (i < num) {
        byte_ptr[i] = (unsigned char)value;
        i++;
    }
    return ptr;
}
