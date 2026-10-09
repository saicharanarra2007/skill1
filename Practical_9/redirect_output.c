/*
 * Practical 9 - I/O Redirection using dup2() - Redirect stdout
 *
 * Aim: To demonstrate how dup2() can redirect standard output (fd 1)
 * to a file, simulating shell '>' redirection.
 *
 * Compile: gcc -Wall -Wextra -g redirect_output.c -o redirect_output
 * Run:     ./redirect_output
 * Check:   cat output.txt
 */
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(void)
{
    int fd;

    /* Open the output file */
    fd = open("output.txt",
              O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }

    /* This prints to the terminal (before redirection) */
    printf("Before redirection: this goes to terminal\n");
    fflush(stdout);   /* Flush before redirecting */

    /* Redirect stdout (file descriptor 1) to output.txt */
    if (dup2(fd, STDOUT_FILENO) == -1)
    {
        perror("dup2");
        close(fd);
        exit(EXIT_FAILURE);
    }

    /* Original fd is no longer needed after dup2 */
    close(fd);

    /* These messages now go to output.txt, not the terminal */
    printf("Hello from redirected standard output!\n");
    printf("This message is stored in output.txt\n");
    printf("dup2() makes fd 1 point to output.txt\n");

    return 0;
}
