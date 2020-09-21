
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <math.h>
#include <pthread.h>
#include <semaphore.h>

//return void pointer

int MAX = 50000, i1 = 0;
int ar[3] = {};
//static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

sem_t mutex;
int count = 0;
void *start_counting(void *arg)
{
    for (;;)
    {
        sem_wait(&mutex);
        count++;
        printf("[THREAD ENTERED] %d\n", *(int *)arg);
        printf("[NUMBER OF THREADS IN CRITICAL SECTION] %d\n", count);
        if (i1 >= MAX)
        {
            count--;
            sem_post(&mutex);
            printf("[THREAD EXITED] %d\n", *(int *)arg);
            return NULL;
        }
        ++i1;
        ar[*(int *)arg]++;
        //sleep((*(int *)arg - 0.5)*0.9);
        count--;
        sem_post(&mutex);
        printf("[THREAD EXITED] %d\n", *(int *)arg);
    }
}

int main(int argc, char **argv)
{
    sem_init(&mutex, 0, 1);
    pthread_t *thread_group = (pthread_t *)malloc(sizeof(pthread_t) * 3);

    int j1 = 0, j2 = 1, j3 = 2;
    pthread_create(&thread_group[0], NULL, start_counting, &j1);
    pthread_create(&thread_group[1], NULL, start_counting, &j2);
    pthread_create(&thread_group[2], NULL, start_counting, &j3);

    for (int i = 0; i < 3; i++)
        pthread_join(thread_group[i], NULL);

    //pthread_exit(NULL);

    printf("%d %d %d %d\n", ar[0], ar[1], ar[2], i1);
    if (ar[0] + ar[1] + ar[2] != MAX)
        printf("ERROR=%d \n", ar[0] + ar[1] + ar[2]);
    else
        printf("SYNCED \n");
    printf("\n");
    free(thread_group);
    //cout<<ar[0]<<" "<<ar[1]<<" "<<ar[2]<<"\n";
    return 0;
}