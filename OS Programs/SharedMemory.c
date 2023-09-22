#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main() {
    int shmid;
    key_t key = ftok("/tmp", 'P'); // Generate a key for the shared memory segment
    char *shared_memory;
    
    // Create a shared memory segment with read and write permissions
    shmid = shmget(key, 1024, IPC_CREAT | 0666);
    
    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }
    
    // Attach the shared memory segment to the process's address space
    shared_memory = (char *)shmat(shmid, NULL, 0);
    
    if (shared_memory == (char *)-1) {
        perror("shmat");
        exit(1);
    }
    
    pid_t child_pid = fork(); // Create a child process
    
    if (child_pid == -1) {
        perror("fork");
        exit(1);
    }
    
    if (child_pid == 0) {
        // Child process writes data to shared memory
        sprintf(shared_memory, "Hello from the child process!");
        exit(0);
    } else {
        // Parent process reads data from shared memory
        wait(NULL); // Wait for the child to exit
        printf("Parent process received: %s\n", shared_memory);
        
        // Detach and remove the shared memory segment
        shmdt(shared_memory);
        shmctl(shmid, IPC_RMID, NULL);
    }
    
    return 0;
}

