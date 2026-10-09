/*
 * Practical 8 - Intentional Memory Leak Demo for Valgrind
 *
 * This program intentionally leaks memory so students can see
 * Valgrind detecting and reporting the leak.
 *
 * Compile: gcc -Wall -Wextra -g memory_leak_demo.c -o memory_leak_demo
 * Run with Valgrind:
 *   valgrind --leak-check=full --show-leak-kinds=all ./memory_leak_demo
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void leaky_function(void)
{
    /* This allocation is NEVER freed - it leaks! */
    char *buffer = malloc(100);
    if (buffer == NULL)
        return;

    strcpy(buffer, "This memory is leaked!");
    printf("leaky_function: allocated 100 bytes at %p\n", (void *)buffer);
    /* Missing: free(buffer); */
}

int main(void)
{
    int *leak1;
    double *leak2;

    printf("=== Memory Leak Demonstration ===\n\n");

    /* Leak 1: Simple integer array */
    leak1 = malloc(10 * sizeof(int));
    if (leak1 == NULL)
        return 1;
    printf("Allocated 40 bytes for leak1 at %p (not freed)\n", (void *)leak1);

    /* Leak 2: Double array */
    leak2 = malloc(5 * sizeof(double));
    if (leak2 == NULL)
        return 1;
    printf("Allocated 40 bytes for leak2 at %p (not freed)\n", (void *)leak2);

    /* Leak 3: Inside a function */
    leaky_function();

    printf("\nProgram ending WITHOUT freeing memory.\n");
    printf("Run with Valgrind to detect leaks:\n");
    printf("valgrind --leak-check=full ./memory_leak_demo\n");

    /* Intentionally NOT freeing leak1 and leak2 */
    return 0;
}
