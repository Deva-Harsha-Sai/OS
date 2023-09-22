#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main() {
    const char *fifoName = "myfifo";
    const char *message = "Hello, FIFO!";
    char buffer[100];

    // Create the FIFO
    if (mkfifo(fifoName, 0666) == -1) {
        perror("mkfifo");
        exit(EXIT_FAILURE);
    }

    printf("FIFO created successfully!\n");

    // Fork a child process for writing
    pid_t child_pid = fork();

    if (child_pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (child_pid == 0) {
        // Child process (Writer)
        int fd = open(fifoName, O_WRONLY);
        if (fd == -1) {
            perror("open");
            exit(EXIT_FAILURE);
        }

        write(fd, message, strlen(message) + 1);
        close(fd);
        exit(EXIT_SUCCESS);
    } else {
        // Parent process (Reader)
        int fd = open(fifoName, O_RDONLY);
        if (fd == -1) {
            perror("open");
            exit(EXIT_FAILURE);
        }

        ssize_t bytesRead = read(fd, buffer, sizeof(buffer));
        close(fd);

        if (bytesRead > 0) {
            printf("Received: %s\n", buffer);
        }

        // Wait for the child process to complete
        wait(NULL);

        // Remove the FIFO file
        if (unlink(fifoName) == -1) {
            perror("unlink");
            exit(EXIT_FAILURE);
        }
    }

    return 0;
}

