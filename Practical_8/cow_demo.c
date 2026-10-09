/*
 * Practical 8 - Copy-on-Write (COW) Demonstration
 *
 * Aim: To observe Copy-on-Write behavior in Linux after fork().
 * When a child process modifies a page, the OS creates a private copy.
 *
 * Compile: gcc -Wall -Wextra -g cow_demo.c -o cow_demo
 * Run:     ./cow_demo
 *
 * To observe COW: monitor /proc/<PID>/status (VmRSS) before and
 * after the child modifies memory.
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define SIZE (10 * 1024 * 1024)   /* 10 MB */

int main(void)
{
    char *data;

    /* Allocate 10 MB */
    data = malloc(SIZE);
    if (data == NULL)
    {
        perror("malloc");
        return 1;
    }

    /* Initialize memory - this touches every page */
    for (size_t i = 0; i < SIZE; i++)
    {
        data[i] = 1;
    }

    printf("Parent PID: %d\n", getpid());
    printf("Allocated and initialized 10 MB.\n");
    printf("\nFork will now be performed...\n");

    pid_t pid = fork();
    if (pid < 0)
    {
        perror("fork");
        free(data);
        return 1;
    }

    if (pid == 0)
    {
        /* Child process */
        printf("\nChild PID: %d, Parent PID: %d\n", getpid(), getppid());
        printf("Child has inherited the memory (COW - no copy yet).\n");
        printf("Check RSS memory: cat /proc/%d/status | grep VmRSS\n", getpid());

        sleep(2);  /* Give time to check memory before modification */

        /*
         * Modify one byte per 4 KB page.
         * This triggers COW: OS allocates a new physical page for each touch.
         */
        for (size_t i = 0; i < SIZE; i += 4096)
        {
            data[i] = 2;
        }

        printf("\nChild modified one byte in every 4 KB page (COW triggered).\n");
        printf("Check RSS memory again: cat /proc/%d/status | grep VmRSS\n", getpid());

        sleep(2);
        free(data);
        return 0;
    }
    else
    {
        /* Parent process */
        printf("\nParent PID: %d, Child PID: %d\n", getpid(), pid);
        printf("Parent and child initially share physical pages (COW).\n");

        wait(NULL);
        printf("\nChild has terminated.\n");
        free(data);
    }

    return 0;
}
