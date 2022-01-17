/*
 *  This header file is for programming #3.  
 *  You may need to add more comments to explain your code ... 
 */

#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

#define BUFFER_SIZE 5   // rounded buffer size

#define PRODUCERS 3  // number of producers
#define CONSUMERS 5  // number of consumers

#define ITERATIONS 60   // number of actions producers/consumers perform 
#define PRODUCER_ITERATIONS (ITERATIONS / PRODUCERS)  //number of actions each producer performs
#define CONSUMER_ITERATIONS (ITERATIONS / CONSUMERS) //number of actions each consumer performs

typedef struct {
    int value[BUFFER_SIZE];
    int next_in, next_out;
} buffer_t;    // struct of bounded buffer


buffer_t buffer;   //global variable: rounded buffer

pthread_t consumer_tid[CONSUMERS], producer_tid[PRODUCERS]; // producer and consumer threads


//TODO: You may need to add more global variables here ...
sem_t full;		// This will block producers if the buffer is full
sem_t empty;	// This will block consumers if the buffer is empty
pthread_mutex_t buffer_mutex;	// Protects the buffer from race conditions

void initilization();
void *consumer(void *param);
void *producer(void *param);



