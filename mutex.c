#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <math.h>
#include <pthread.h>

//return void pointer
/*
    [IMPORTANT INFO ON MUTEX FLAGS]
https://stackoverflow.com/questions/5454746/pthread-mutex-lock-unlock-by-different-threads/5492499#5492499
*/
int MAX = 50000, i1 = 0;
int ar[3] = {};
static pthread_mutex_t mutex = PTHREAD_ERRORCHECK_MUTEX_INITIALIZER_NP;
void *start_counting(void *arg)
{
    for (;;)
    {
        pthread_mutex_lock(&mutex);
        if (i1 >= MAX)
        {
            pthread_mutex_unlock(&mutex);
            return NULL;
        }
        int *num = (int *)arg;
        ar[*num]++;
        double x = 2;
        double y = *num;
        double p;
        p = 0.5*sqrt(*num+1);
        sleep(p);
        ++i1;

        

        
        pthread_mutex_unlock(&mutex);
        

        printf("thread number %d executed %d times and current count is %d\n", *num, ar[*num], i1);
        
        //sleep(p);
    }
    //pthread_exit(NULL);
}
// void *h1(void *arg)
// {
//     int *ch = (int *)arg;

//     for (int i = 0; i < 10; i++)
//     {
//         ar[*ch]++;
//         printf("%d thread is printing %d\n", *ch, i);
//         sleep(1* *ch);
//     }
// }
int main(int argc, char **argv)
{
    pthread_t *thread_group =(pthread_t *) malloc(sizeof(pthread_t) * 3);

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
