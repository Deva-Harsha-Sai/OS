#include <stdio.h>

struct Process {
    int id;
    int arrivalTime;
    int burstTime;
};

void roundRobin(struct Process processes[], int n, int quantum) {
    int remainingTime[n];
    int i;
    for (i = 0; i < n; i++) {
        remainingTime[i] = processes[i].burstTime;
    }
    
    int time = 0;
    int done = 0;
    
    while (done < n) {
        for (i = 0; i < n; i++) {
            if (remainingTime[i] > 0) {
                int executeTime = (remainingTime[i] > quantum) ? quantum : remainingTime[i];
                printf("Process %d runs for %d units.\n", processes[i].id, executeTime);
                remainingTime[i] -= executeTime;
                time += executeTime;
                
                if (remainingTime[i] == 0) {
                    done++;
                    printf("Process %d is completed.\n", processes[i].id);
                }
            }
        }
    }
}

int main() {
    struct Process processes[] = {
        {1, 0, 10},
        {2, 1, 5},
        {3, 2, 8},
    };
    int n = sizeof(processes) / sizeof(processes[0]);
    int quantum = 2;
    
    printf("Round Robin Scheduling:\n");
    roundRobin(processes, n, quantum);
    
    return 0;
}

