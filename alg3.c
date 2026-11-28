#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#include "common.h"
#include "common_threads.h"
#include "zemaphore.h"

// #define MAXN 20 //maximum number of forks can be 20

#define THINK_TIME  1 //secs spent thinking
#define EAT_TIME    1 //secs spent eating
#define DELAY   1 //secs between picking up the two forks?

int N;
Zem_t forks[20];
int meals[20];
Zem_t table;

//same structure as void child in littleOldWoman
void *philosopher(void *arg) { 
    long long int value = (long long int) arg;
    int p = (int) value;
    
    int left = p;
    int right = (p+1) % N;

    // sleep(THINK_TIME);
    while(1)
    {
        sleep(THINK_TIME);
        //let philosophers sit down
        Zem_wait(&table);
        
        //hold right fork
        Zem_wait(&forks[right]);
        printf("philosopher %d is holding right fork %d\n",p, right);

        //delay before holding next fork
        sleep(DELAY);

        //hold left fork
        Zem_wait(&forks[left]);
        printf("philosopher %d is holding left fork %d\n",p, left);
        
        //philosopher eats
        printf("philosopher %d is eating :)\n",p);
        meals[p]++; //to find the distribution of meals across philosophers
        sleep(EAT_TIME);

        //done eating: give up the left and then right fork
        Zem_post(&forks[left]);
        Zem_post(&forks[right]);

        //let phil get up
        Zem_post(&table);

        printf("philosopher %d is done eating.\n", p);
        sleep(2);
       
    }
   
    return NULL;
}
int main(int argc, char *argv[]) {
    N = atoi(argv[1]); //number of phil taken as command line arg
    //atoi: ascii to integer

    //initialize table semaphore
    Zem_init(&table, N-1); //for N-1 seats

    //need to initialize all forks
    for (int i = 0; i < N; ++i)
    {
        Zem_init(&forks[i], 1);
    }

    //multiple threads
    pthread_t threads[20];
    for (int i = 0; i < N; ++i)
    {
        // pthread_t c;
        long long int me = i;
        Pthread_create(&threads[i], NULL, philosopher, (void *)me);
    }
    
    sleep(20); //have enough time to let threads create.
    printf("\n");
    printf("meals per philosopher: \n"); //for tracking
    for (int i = 0; i <N; i++){
        printf("philosopher %d ate %d times\n", i, meals[i]);
    }
    printf("\n");
    printf("philsopher alg3 end\n");
    return 0;
}
