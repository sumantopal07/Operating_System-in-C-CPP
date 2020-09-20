#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <math.h>
#include <pthread.h>

//return void pointer

int MAX = 50, i1 = 0;
int ar[3] = {};
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
void *fx(void *args)
{
    int *ptr = (int *)malloc(sizeof(int));
    // static int x=9;
    *ptr = 8;
    return ptr;
}
void *start_counting(void *arg)
{
    for (;;)
    {
        pthread_mutex_lock(&mutex);
        if (i1 >= MAX)
        {
            pthread_mutex_unlock(&mutex);
            int *ptr = (int *)malloc(sizeof(int));
            // static int x=9;
            *ptr = 8;
            return ptr;
        }
        int *num = (int *)arg;
        ar[*num]++;
        double p;
        p = 0.5 * sqrt(*num + 1);
        sleep(p);
        ++i1;

        pthread_mutex_unlock(&mutex);

        printf("thread number %d executed %d times and current count is %d\n", *num, ar[*num], i1);
        //free(num);
        //sleep(p);
    }
    printf("%d \n", i1);
    int *ptr = (int *)malloc(sizeof(int));
    // static int x=9;
    *ptr = 8;
    return ptr;
    //pthread_exit(NULL);
}
int main(int argc, char **argv)
{
    pthread_t *thread_group = (pthread_t *)malloc(sizeof(pthread_t));

    int j1 = 0, j2 = 1, j3 = 2;
    pthread_create(&thread_group[0], NULL, start_counting, &j1);
    // pthread_create(&thread_group[1], NULL, start_counting, &j2);
    // pthread_create(&thread_group[2], NULL, start_counting, &j3);

    // void *result0;
    int *x;
    pthread_join(thread_group[0], (void **)&x);
    //pthread_join(thread_group[1], (void*)&result1);
    // pthread_join(thread_group[2], (void*)&result2);

    printf("%d ", *x);
    free(x);
    // free(result1);
    // free(result2);
    //return 0;

    // //pthread_exit(NULL);

    // printf("%d %d %d %d\n", ar[0], ar[1], ar[2], i1);
    // if (ar[0] + ar[1] + ar[2] != MAX)
    //     printf("ERROR=%d \n", ar[0] + ar[1] + ar[2]);
    // else
    //     printf("SYNCED \n");
    // printf("\n");

    free(thread_group);
    //cout<<ar[0]<<" "<<ar[1]<<" "<<ar[2]<<"\n";
    return 0;
}
//g++ -o a a.cpp -lpthread -lm -Wshadow -Wall -g  -fsaniti=address -fsanitize=undefined -D_GLIBCXX_DEBUG