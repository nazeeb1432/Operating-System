#include<stdio.h>
#include<stdlib.h>
#include<semaphore.h>
#include<pthread.h>
#include<unistd.h>

#define NUM_THREADS 3
#define BUFFER_SIZE 10
#define true 1

sem_t empty, full, mutex;

// ||||||

typedef struct Buffer{
    int sharedBuffer[BUFFER_SIZE];
    int in;
    int out;
}Buffer;

Buffer buffer; 
int i;

void init_buffer();
void init_semaphores();
void destroy_semaphores();
void *produce(void *param);
void *consume(void *param);
void *consume(void *param);

int main(){

    init_buffer();
    init_semaphores();

    pthread_t producer[NUM_THREADS], consumer[NUM_THREADS];

    for(i = 0; i < NUM_THREADS; ++i){
        pthread_create(&producer[i], NULL, produce, NULL);
        pthread_create(&consumer[i], NULL, consume, NULL);
    }
    
    for(i = 0; i < NUM_THREADS; ++i){
        pthread_join(producer[i],NULL);
        pthread_join(consumer[i],NULL);
    }
    
    destroy_semaphores();

    return 0;
}

void *produce(void *param){
    do{
        int next_produced;
        next_produced = rand()%20;

        sem_wait(&empty); // 10
        sem_wait(&mutex); // 0
        
        buffer.sharedBuffer[buffer.in] = next_produced;

        printf("Produced item %d at index %d\n", next_produced, buffer.in);

        buffer.in = ( buffer.in + 1 ) % BUFFER_SIZE;
        
        sem_post(&mutex); // 1
        sem_post(&full); // 1
        
        sleep(rand()%3);
    }while(true);
}

void *consume(void *param){
    do{
        sem_wait(&full);
        sem_wait(&mutex);

        int next_consumed;
        next_consumed = buffer.sharedBuffer[buffer.out];
        
        printf("Item consumed %d from index %d\n", next_consumed, buffer.out);
        
        buffer.out = ( buffer.out + 1 ) % BUFFER_SIZE;
        

        sem_post(&mutex);
        sem_post(&empty);

        sleep(rand()%3);
    }while(true);
}

void init_buffer(){
    for(i = 0; i < BUFFER_SIZE; ++i) buffer.sharedBuffer[i] = 0;
    buffer.in = 0;
    buffer.out = 0;
}

void init_semaphores(){
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    sem_init(&mutex, 0, 1);
}

void destroy_semaphores(){
    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);
}