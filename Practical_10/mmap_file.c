/*
 * Practical 10 (Extended) - File I/O Using mmap()
 *
 * Aim: To perform file reading and modification using memory-mapped I/O
 * and compare with traditional read()/write() operations.
 *
 * Compile: gcc -Wall -Wextra -g mmap_file.c -o mmap_file
 * Setup:   echo "Linux memory mapped file I/O demonstration" > data.txt
 * Run:     ./mmap_file
 */
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <string.h>

int main(void)
{
    int fd;
    struct stat st;
    char *data;

    /* Open file for reading and writing */
    fd = open("data.txt", O_RDWR);
    if (fd == -1)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }

    /* Obtain file size */
    if (fstat(fd, &st) == -1)
    {
        perror("fstat");
        close(fd);
        exit(EXIT_FAILURE);
    }

    if (st.st_size == 0)
    {
        printf("File is empty.\n");
        close(fd);
        return 0;
    }

    /* Map file into process virtual memory */
    data = mmap(NULL,
                st.st_size,
                PROT_READ | PROT_WRITE,
                MAP_SHARED,
                fd,
                0);
    if (data == MAP_FAILED)
    {
        perror("mmap");
        close(fd);
        exit(EXIT_FAILURE);
    }

    /* Read file contents through mapped memory */
    printf("Original file contents:\n");
    fwrite(data, 1, st.st_size, stdout);
    printf("\n\nModifying file via mmap...\n");

    /* Modify first 5 characters directly in memory */
    if (st.st_size >= 5)
    {
        memcpy(data, "HELLO", 5);
    }

    /* Synchronize changes with the underlying file */
    if (msync(data, st.st_size, MS_SYNC) == -1)
    {
        perror("msync");
    }

    printf("File modified using mmap(). First 5 bytes changed to 'HELLO'.\n");

    /* Remove memory mapping */
    if (munmap(data, st.st_size) == -1)
    {
        perror("munmap");
    }

    close(fd);
    return 0;
}
