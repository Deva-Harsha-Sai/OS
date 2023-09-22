#include <stdio.h>

struct Process {
    int id;
    int priority;
    int burstTime;
};

void priorityQueue(struct Process processes[], int n) {
    int time = 0;
    
    while (n > 0) {
        int highestPriority = -1;
        int highestPriorityIndex = -1;
        int i;
        for (i = 0; i < n; i++) {
            if (processes[i].priority > highestPriority && processes[i].burstTime > 0) {
                highestPriority = processes[i].priority;
                highestPriorityIndex = i;
            }
        }
        
        if (highestPriorityIndex == -1) {
            time++;
        } else {
            printf("Process %d (Priority %d) runs for 1 unit.\n", processes[highestPriorityIndex].id, processes[highestPriorityIndex].priority);
            processes[highestPriorityIndex].burstTime--;
            time++;
            
            if (processes[highestPriorityIndex].burstTime == 0) {
                printf("Process %d (Priority %d) is completed.\n", processes[highestPriorityIndex].id, processes[highestPriorityIndex].priority);
                for (i = highestPriorityIndex; i < n - 1; i++) {
                    processes[i] = processes[i + 1];
                }
                n--;
            }
        }
    }
}

int main() {
    struct Process processes[] = {
        {1, 3, 8},
        {2, 1, 6},
        {3, 4, 9},
        {4, 2, 12}
    };
    int n = sizeof(processes) / sizeof(processes[0]);
    
    printf("Priority Queue Scheduling:\n");
    priorityQueue(processes, n);
    
    return 0;
}

