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
int fork_in_use[20];
int meals[20];
Zem_t lock; //protects fork in use

//same structure as void child in littleOldWoman
void *philosopher(void *arg) { 
    long long int value = (long long int) arg;
    int p = (int) value;
    
    int left = p;
    int right = (p+1) % N;

    
    while(1)
    {
        sleep(THINK_TIME);

        //isolate the rogue philosopher
        if (p == 0){
            // sleep(1); //rogue becomes slower to get hungry.

            Zem_wait(&lock);
            int left_free = (fork_in_use[left] == 0);
            Zem_post(&lock);

            if (left_free){
                //left fork free: get left first then right
                Zem_wait(&forks[left]);
                Zem_wait(&lock);
                fork_in_use[left] = 1;
                Zem_post(&lock);
                printf("philosopher %d is holding left fork %d\n",p, left);

                sleep(DELAY);

                //now grab right fork
                Zem_wait(&forks[right]);
                Zem_wait(&lock);
                fork_in_use[right] = 1;
                Zem_post(&lock);
                printf("philosopher %d is holding right fork %d\n",p, right);

            }
            else {
                //left is taken: so right fork first, then left
                Zem_wait(&forks[right]);
                Zem_wait(&lock);
                fork_in_use[right] = 1;
                Zem_post(&lock);
                printf("philosopher %d is holding right fork %d\n",p, right);

                sleep(DELAY);
                //grab left fork
                Zem_wait(&forks[left]);
                Zem_wait(&lock);
                fork_in_use[left] = 1;
                Zem_post(&lock);
                printf("philosopher %d is holding left fork %d\n",p, left);

            }    
            
        }
        
        else {
        //normal execution: left fork then right fork
            Zem_wait(&forks[left]);
            Zem_wait(&lock);
            fork_in_use[left] = 1;
            Zem_post(&lock);
            printf("philosopher %d is holding left fork %d\n",p, left);
            
            //delay before holding next fork
            sleep(DELAY);
            
            //hold right fork
            Zem_wait(&forks[right]);
            Zem_wait(&lock);
            fork_in_use[right] = 1;
            Zem_post(&lock);
            printf("philosopher %d is holding right fork %d\n",p, right);
        }
        //philosopher eats
        printf("philosopher %d is eating :)\n",p);
        meals[p]++;
        sleep(EAT_TIME);
            
        //done eating: give up the left and then right fork
        Zem_wait(&lock);
        fork_in_use[left] = 0;
        fork_in_use[right] = 0;
        Zem_post(&lock);

        Zem_post(&forks[left]);
        Zem_post(&forks[right]);
        printf("philosopher %d is done eating \n", p);
        sleep(2);
        }
    
    return NULL;
}
int main(int argc, char *argv[]) {
    N = atoi(argv[1]); //number of phil taken as command line arg
    //atoi: ascii to integer

    //initilize lock
    Zem_init(&lock, 1);
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
   
    sleep(20); //sleep for 20 secs
    printf("\n");
    printf("meals per philosopher: \n"); //for tracking
    for (int i = 0; i <N; i++){
        printf("philosopher %d ate %d times\n", i, meals[i]);
    }

    printf("philsopher alg4 end\n");
    return 0;
}
