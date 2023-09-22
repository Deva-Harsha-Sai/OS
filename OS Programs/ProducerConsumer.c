#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
sem_t empty, full;
pthread_mutex_t mutex;

void *producer(void *arg) {
    int item;
    int i;
    for (i = 0; i < 10; i++) {
        item = i;  // Produce an item

        sem_wait(&empty); // Wait if the buffer is full
        pthread_mutex_lock(&mutex);
        
        // Add item to the buffer
        buffer[i % BUFFER_SIZE] = item;
        printf("Produced: %d\n", item);
        
        pthread_mutex_unlock(&mutex);
        sem_post(&full); // Signal that the buffer is not empty
    }
    pthread_exit(NULL);
}

void *consumer(void *arg) {
    int item;
    int i;
    for (i = 0; i < 10; i++) {
        sem_wait(&full); // Wait if the buffer is empty
        pthread_mutex_lock(&mutex);

        // Remove item from the buffer
        item = buffer[i % BUFFER_SIZE];
        printf("Consumed: %d\n", item);
        
        pthread_mutex_unlock(&mutex);
        sem_post(&empty); // Signal that the buffer is not full
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t producer_thread, consumer_thread;

    sem_init(&empty, 0, BUFFER_SIZE); // Initialize empty semaphore to buffer size
    sem_init(&full, 0, 0);           // Initialize full semaphore to 0
    pthread_mutex_init(&mutex, NULL);

    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}

