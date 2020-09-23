#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <math.h>
#include <pthread.h>
#include <semaphore.h>

using namespace std;



//First readers-writers problem
/*
The first solution is suboptimal, because it is possible 
that a reader R1 might have the lock, a writer W be waiting for the lock, 
and then a reader R2 requests access. It would be unfair for R2 
to jump in immediately, ahead of W; if that happened often enough, 
W would starve.Instead, W should start as soon as possible. 
*/

int readers;
sem_t mutex, db;

void *reader(void *args)
{
    sleep(1.4);
    sem_wait(&mutex); //Ensure that no other
                      //reader can execute the <Entry> section while you are in it

    /*<ENTRY SECURITY SECTION>*/ //to avoid race conditon on readers

    readers++;
    //cout << readers << " ";

    if (readers == 1)
        sem_wait(&db); //If you are the first reader,
                       //lock the resource from writers.
                       // Resource stays reserved for subsequent readers

    /*<EXIT SECURITY SECTION>*/

    sem_post(&mutex); //Release

    // Do the reading
    sleep(1.4);
    

    sem_wait(&mutex); //Ensure that no other
                      //reader can execute the <Exit> section while
                      //you are in it
    /*<CRITICAL SECTION>*/
    printf("%d readers in DB\n",readers);

    readers--; //Indicate that you are no longer
               //needing the shared resource. One fewer reader

    if (readers == 0)  //Checks if you are the last (only) reader
                       //who is reading the shared file
        sem_post(&db); //If you are last reader, then you can unlock the
                       //resource. This makes it available to writers.

    /*<EXIT CRITICAL SECTION>*/

    sem_post(&mutex); //Release

    return NULL;
}
void *writer(void *args)
{
   // sleep(2);

    sem_wait(&db); //Lock the shared file for a writer

    /*<CRITICAL SECTION>*/
    printf("\t\t\t\t\tWriter and %d readers in DB\n",readers);

    /*<EXIT CRITICAL SECTION>*/

    //sleep(0.01);
    sem_post(&db); //Release the shared file for use by other readers.
                   //Writers are allowed if there are no readers requesting it.
    //sleep(1);
    return NULL;
}
int main(int argc, char **argv)
{
    pthread_t *t1=(pthread_t *)malloc(sizeof(pthread_t)*10);
    pthread_t *t2=(pthread_t *)malloc(sizeof(pthread_t)*3);

    sem_init(&mutex, 0, 1);
    sem_init(&db, 0, 1);

    for(int i=0;i<10;i++)
        pthread_create(&t1[i], NULL, reader, NULL);
    for(int i=0;i<3;i++)
        pthread_create(&t2[i], NULL, writer, NULL);

    for(int i=0;i<10;i++)
        pthread_join(t1[i], NULL);
    for(int i=0;i<3;i++)
        pthread_join(t2[i], NULL);

    free(t1);
    free(t2);
    return 0;
}