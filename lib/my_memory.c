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

/**
 * @brief Allocates memory and initializes it to zero
 * 
 * @param size Size of memory to allocate
 * @return Pointer to allocated memory
 */
void *my_malloc(size_t size)
{
    void *ptr = malloc(size);

    if (ptr)
        my_memset(ptr, 0, size);
    return ptr;
}

/**
 * @brief Frees allocated memory
 * @param ptr Pointer to memory to free
 */
void my_free(void *ptr)
{
    if (ptr)
        free(ptr);
}

/**
 * @brief Sets memory to a specific value
 * @param ptr Pointer to memory block
 * @param value Value to set (as unsigned char)
 * @param num Number of bytes to set
 * @return Pointer to the memory block
 */
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
