#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <math.h>
#include <pthread.h>
#include <semaphore.h>

using namespace std;

//Producer Consumer Problem

int cakes = 0;
sem_t mutex, empty_slots, free_slots;

void *producer(void *args)
{
    while (true)
    {
        // sem_wait(&empty_slots);
        // sleep(0.7);
        // sem_wait(&mutex);
        // sleep(0.8);
        while(cakes==3)
        {
            cout<<"PRODUCER HALT\n";
            sleep(1.33);
        }
        cout<<"Producing an "<<++cakes<<" item\n";
        sleep(1.23);
        // sem_post(&mutex);
        // sleep(0.26);
        // sem_post(&free_slots);
    }
    return NULL;
}
void *consumer(void *args)
{
    while (true)
    {
        while(cakes==0)
        {
            cout<<"CONSUMER HALT\n";
            sleep(1.1);
        }
        cout<<"consuming an "<<cakes--<<" item\n";
        sleep(1.99);
        // sem_wait(&free_slots);
        // sleep(0.2);
        // sem_wait(&mutex);
        // sleep(1.25);
        // cout<<"Consuming item\n";
        // sem_post(&mutex);
        // sleep(0.26);
        // sem_post(&empty_slots);
    }
    return NULL;
}
int main(int argc, char **argv)
{
    pthread_t t1, t2;

    sem_init(&mutex, 0, 1);
    sem_init(&free_slots, 0, 2);
    sem_init(&empty_slots, 0, 0);

    pthread_create(&t1, NULL, producer, NULL);
    pthread_create(&t2, NULL, consumer, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    return 0;
}