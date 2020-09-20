#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
//return void pointer
void *entry_point(void *x)
{
    int *num=(int *) x;
    printf("hello from the second thread :) %d",*num);

    return NULL;
}
int main(int argc, char **argv)
{
    pthread_t thread;

    printf("Hello world\n");

    int num = 123;

    pthread_create(&thread, NULL, entry_point, &num);
    //pthread_create(reference to thread struct, pthread attributes, (void*)entry point of function,send data);

    pthread_join(thread, NULL);
    //pthread_join(thread,NULL);//main thread wait untill your created thread finishes;

    return 0;
}
