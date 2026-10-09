/*
 * Practical 7 - Process Memory Layout Investigation
 * 
 * Aim: To investigate the virtual memory layout of a process using
 * /proc/<PID>/maps and related tools.
 *
 * Compile: gcc -Wall -Wextra -g memory_demo.c -o memory_demo
 * Run:     ./memory_demo
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* Initialized global variable - Data segment */
int global_var = 100;

/* Uninitialized global variable - BSS segment */
int global_uninitialized;

int main(void)
{
    /* Static variable - Data segment */
    static int static_var = 200;

    /* Stack variable */
    int stack_var = 300;

    /* Heap allocation */
    int *heap_var = malloc(sizeof(int));

    if (heap_var == NULL)
    {
        perror("malloc");
        return 1;
    }

    *heap_var = 400;

    printf("Process ID (PID): %d\n", getpid());
    printf("Address of code   : %p\n", (void *)main);
    printf("Address of global : %p\n", (void *)&global_var);
    printf("Address of static : %p\n", (void *)&static_var);
    printf("Address of BSS    : %p\n", (void *)&global_uninitialized);
    printf("Address of heap   : %p\n", (void *)heap_var);
    printf("Address of stack  : %p\n", (void *)&stack_var);

    printf("\nProcess is running. Open another terminal and run:\n");
    printf("cat /proc/%d/maps\n", getpid());
    printf("pmap %d\n", getpid());
    printf("\nSleeping for 60 seconds...\n");

    sleep(60);

    free(heap_var);
    return 0;
}
