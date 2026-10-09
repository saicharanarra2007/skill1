/*
 * Practical 10 (Extended) - Traditional File I/O using read()/write()
 *
 * Aim: To perform file reading and modification using traditional system calls
 * and compare with memory-mapped I/O (mmap()).
 *
 * Compile: gcc -Wall -Wextra -g read_write_file.c -o read_write_file
 * Setup:   echo "Linux memory mapped file I/O demonstration" > data.txt
 * Run:     ./read_write_file
 */
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 4096

int main(void)
{
    int fd;
    ssize_t bytes_read;
    char buffer[BUFFER_SIZE];

    /* Open file for reading and writing */
    fd = open("data.txt", O_RDWR);
    if (fd == -1)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }

    /* Read file contents into buffer */
    bytes_read = read(fd, buffer, BUFFER_SIZE - 1);
    if (bytes_read == -1)
    {
        perror("read");
        close(fd);
        exit(EXIT_FAILURE);
    }
    buffer[bytes_read] = '\0';

    printf("Original file contents:\n%s\n", buffer);

    /* Move file offset back to beginning for writing */
    if (lseek(fd, 0, SEEK_SET) == -1)
    {
        perror("lseek");
        close(fd);
        exit(EXIT_FAILURE);
    }

    /* Modify first five characters in buffer */
    if (bytes_read >= 5)
    {
        buffer[0] = 'H';
        buffer[1] = 'E';
        buffer[2] = 'L';
        buffer[3] = 'L';
        buffer[4] = 'O';
    }

    /* Write modified contents back to file */
    if (write(fd, buffer, bytes_read) == -1)
    {
        perror("write");
        close(fd);
        exit(EXIT_FAILURE);
    }

    printf("\nFile modified using read()/write(). First 5 bytes changed to 'HELLO'.\n");
    close(fd);
    return 0;
}
