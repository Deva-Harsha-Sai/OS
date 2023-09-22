#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid;
    int status;
    
    pid = fork(); // Create a child process
    
    if (pid == -1) {
        perror("fork");
        return 1;
    }
    
    if (pid == 0) {
        // Child process
        printf("This is the child process (PID: %d).\n", getpid());
    } else {
        // Parent process
        printf("This is the parent process (PID: %d).\n", getpid());
        wait(&status); // Wait for the child to exit
    }
    
    return 0;
}

