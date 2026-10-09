/*
 * Practical 9 - I/O Redirection using dup2() - Redirect stdin
 *
 * Aim: To demonstrate how dup2() can redirect standard input (fd 0)
 * from a file, simulating shell '<' redirection.
 *
 * Compile: gcc -Wall -Wextra -g redirect_input.c -o redirect_input
 * Setup:   echo -e "Operating Systems\nLinux File I/O\ndup2 system call" > input.txt
 * Run:     ./redirect_input
 */
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(void)
{
    int fd;
    char buffer[100];

    /* Open input file for reading */
    fd = open("input.txt", O_RDONLY);
    if (fd == -1)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }

    /* Redirect stdin (file descriptor 0) to input.txt */
    if (dup2(fd, STDIN_FILENO) == -1)
    {
        perror("dup2");
        close(fd);
        exit(EXIT_FAILURE);
    }
    close(fd);   /* fd is no longer needed after dup2 */

    /* fgets/scanf now reads from input.txt instead of keyboard */
    printf("Reading from redirected standard input:\n");
    while (fgets(buffer, sizeof(buffer), stdin) != NULL)
    {
        printf("%s", buffer);
    }

    return 0;
}
