#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define NUM_READERS 5
#define NUM_WRITERS 2

sem_t mutex;
sem_t wrt;
int readcount = 0;
int data = 0;

void *reader(void *arg) {
    int reader_id = *((int *)arg);
    while (1) {
        sem_wait(&mutex);
        readcount++;
        if (readcount == 1) {
            sem_wait(&wrt);
        }
        sem_post(&mutex);
        
        printf("Reader %d read data: %d\n", reader_id, data);
        
        sem_wait(&mutex);
        readcount--;
        if (readcount == 0) {
            sem_post(&wrt);
        }
        sem_post(&mutex);
        
        // Simulate reading time
        usleep(1000000);
    }
}

void *writer(void *arg) {
    int writer_id = *((int *)arg);
    while (1) {
        sem_wait(&wrt);
        
        data++;
        printf("Writer %d wrote data: %d\n", writer_id, data);
        
        sem_post(&wrt);
        
        // Simulate writing time
        usleep(2000000);
    }
}

int main() {
    pthread_t readers[NUM_READERS];
    pthread_t writers[NUM_WRITERS];
    int i, reader_ids[NUM_READERS], writer_ids[NUM_WRITERS];
    
    sem_init(&mutex, 0, 1);
    sem_init(&wrt, 0, 1);
    
    // Create reader threads
    for (i = 0; i < NUM_READERS; i++) {
        reader_ids[i] = i + 1;
        pthread_create(&readers[i], NULL, reader, &reader_ids[i]);
    }
    
    // Create writer threads
    for (i = 0; i < NUM_WRITERS; i++) {
        writer_ids[i] = i + 1;
        pthread_create(&writers[i], NULL, writer, &writer_ids[i]);
    }
    
    // Join reader threads
    for (i = 0; i < NUM_READERS; i++) {
        pthread_join(readers[i], NULL);
    }
    
    // Join writer threads
    for (i = 0; i < NUM_WRITERS; i++) {
        pthread_join(writers[i], NULL);
    }
    
    sem_destroy(&mutex);
    sem_destroy(&wrt);
    
    return 0;
}
