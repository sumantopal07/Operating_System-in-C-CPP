#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <math.h>
#include <pthread.h>
#include <semaphore.h>
#include <queue>

using namespace std;

//Producer Consumer Problem

queue<int> q;
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
sem_t  empty_slots, filled_slots;
// mutex       : //because non atmic operation inside critical section may lead to inconsistency
// filled_slots: //to keep min_limit on buffer while consumer it
                 // UnderFlow
                 
// empty_slots : Produced keeps producing if not exist
                //to keep max_limit on buffer
                 //OverFlow
int ar[4]={};
int produced=0,consumed=0;
void *producer(void *args)
{
    //sleep(2);
    printf("Producer running %d\n", (int)pthread_self());
    for (int i = 0; ; i++)
    {
        sem_wait(&empty_slots);    //sleep(0.2);
        pthread_mutex_lock(&mutex);

        printf("Produced item %d\n",i);
        produced++;
        q.push(i);

        pthread_mutex_unlock(&mutex);    //sleep(0.3);
        sem_post(&filled_slots);

    }
    return NULL;
}
void *consumer(void *args)
{
    int  temp = -1;
    printf("Consumer running %d\n", *(int *)args);
    for (int i = 0;; i++)
    {
        //sleep(100);
        sem_wait(&filled_slots);    //sleep(0.3);
        pthread_mutex_lock(&mutex);

        temp = q.front();
        printf("Consuming item %d by %d\n", temp,*(int *)args);
        ar[*(int *) args]++;
        consumed++;
        q.pop();
        printf("[STATUS] %d %d %d\n",ar[1],ar[2],ar[3]);
        //sleep(1);
        pthread_mutex_unlock(&mutex);       //sleep(0.6);
        sem_post(&empty_slots); //sleep(1.2);
        assert(produced>=consumed);
    }
    return NULL;
}
int main(int argc, char **argv)
{
    pthread_t t1, t2,t3,t4;

    //sem_init(&mutex, 0, 1);
    sem_init(&filled_slots, 0, 0);
    sem_init(&empty_slots, 0, 6);

    int x1=1,x2=2,x3=3;

    pthread_create(&t1, NULL, producer, NULL);
    pthread_create(&t2, NULL, consumer, &x1);
    pthread_create(&t3, NULL, consumer, &x2);
    pthread_create(&t4, NULL, consumer, &x3);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
    pthread_join(t4, NULL);
    // cout<<ar[1]<<" "<<ar[2]<<" "<<ar[3]<<"\n";
    return 0;
}
