/*
 * Practical 8 - Dynamic Memory Allocation and Memory Leak Detection
 *
 * Aim: To develop a C program using malloc(), calloc(), realloc(), and free(),
 * observe dynamic memory allocation behavior, and identify memory leaks
 * using Valgrind.
 *
 * Compile: gcc -Wall -Wextra -g memory_alloc_demo.c -o memory_alloc_demo
 * Run:     ./memory_alloc_demo
 * Valgrind: valgrind --leak-check=full ./memory_alloc_demo
 */
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int i;
    int *malloc_ptr;
    int *calloc_ptr;
    int *temp;

    /* -----------------------------------
       1. malloc() - allocates uninitialized memory
       ----------------------------------- */
    printf("1. malloc() demonstration\n");
    malloc_ptr = malloc(5 * sizeof(int));
    if (malloc_ptr == NULL)
    {
        printf("malloc() failed\n");
        return 1;
    }

    /* Initialize manually (malloc does NOT zero memory) */
    for (i = 0; i < 5; i++)
    {
        malloc_ptr[i] = (i + 1) * 10;
    }

    printf("Memory allocated using malloc():\n");
    for (i = 0; i < 5; i++)
    {
        printf("%d ", malloc_ptr[i]);
    }
    printf("\n\n");

    /* -----------------------------------
       2. calloc() - allocates zero-initialized memory
       ----------------------------------- */
    printf("2. calloc() demonstration\n");
    calloc_ptr = calloc(5, sizeof(int));
    if (calloc_ptr == NULL)
    {
        printf("calloc() failed\n");
        free(malloc_ptr);
        return 1;
    }

    /* calloc() zeroes memory, so values are already 0 */
    printf("Memory allocated using calloc() (all zeros):\n");
    for (i = 0; i < 5; i++)
    {
        printf("%d ", calloc_ptr[i]);
    }
    printf("\n\n");

    /* -----------------------------------
       3. realloc() - resize existing allocation
       ----------------------------------- */
    printf("3. realloc() demonstration\n");
    /* Expand malloc_ptr from 5 to 10 integers */
    temp = realloc(malloc_ptr, 10 * sizeof(int));
    if (temp == NULL)
    {
        printf("realloc() failed\n");
        free(malloc_ptr);
        free(calloc_ptr);
        return 1;
    }
    malloc_ptr = temp;   /* Only update pointer if realloc succeeded */

    /* Initialize the new elements */
    for (i = 5; i < 10; i++)
    {
        malloc_ptr[i] = (i + 1) * 10;
    }

    printf("Memory after realloc() (5 -> 10 integers):\n");
    for (i = 0; i < 10; i++)
    {
        printf("%d ", malloc_ptr[i]);
    }
    printf("\n\n");

    /* -----------------------------------
       4. free() - release allocated memory
       ----------------------------------- */
    printf("4. free() demonstration\n");
    free(malloc_ptr);
    malloc_ptr = NULL;   /* Set to NULL to prevent dangling pointer */
    free(calloc_ptr);
    calloc_ptr = NULL;
    printf("Allocated memory successfully released.\n");

    return 0;
}
