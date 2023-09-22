#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int fd;
    char buffer[50];
    
    // Create and open a file for writing
    fd = open("example.txt", O_CREAT | O_WRONLY, 0666);
    if (fd == -1) {
        perror("open");
        exit(1);
    }
    
    // Write data to the file
    write(fd, "Hello, world!\n", 13);
    
    // Close the file
    close(fd);
    
    // Open the file for reading
    fd = open("example.txt", O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(1);
    }
    
    // Read data from the file
    int bytesRead = read(fd, buffer, sizeof(buffer));
    if (bytesRead == -1) {
        perror("read");
        exit(1);
    }
    
    // Close the file
    close(fd);
    
    // Print the read data
    printf("Read from file: %s", buffer);
    
    return 0;
}

