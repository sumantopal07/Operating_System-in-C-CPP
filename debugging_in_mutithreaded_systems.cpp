#include <iostream>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
using namespace std;
int count = 0, MAX = 10000,a=0,b=0;
static pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
void *fx(void *args)
{
    for (int i = 0; i < 10000; i++)
    {
       // pthread_mutex_lock(&mutex1);

        if (count >= MAX)
        {
            //pthread_mutex_unlock(&mutex1);
            return NULL;
        }
        count++;
        int* p=(int* )args;
        //cout<<*p<<" ";
        sleep(0.1);
        if(*p==0)
            a++;
        else
            b++;
        //pthread_mutex_unlock(&mutex1);
    }

    return NULL;
}
// GDB COMMANDS:
// -->run
// -->break main
// -->break line
// -->clean line
// -->step( step into the function)
// --> enter( any time repeats the last command)
// -->continue
// -->info threads
// -->thread 1
// -->watch a
// -->next
// --> print var
// --> list
// --> watch counter>=0x4500
// --> break function
// --> quit
// --> break func thread 2
// --> thread apply all backtrace

int main(int argc, char **argv)
{
    pthread_t *t1 =(pthread_t *) malloc(sizeof(pthread_t));
    pthread_t *t2 =(pthread_t *) malloc(sizeof(pthread_t));

    int x=0;
    int y=1;
    pthread_create(t1, NULL, fx, &x);
    pthread_create(t2, NULL, fx, &y);
    //pthread_join(t1[0], NULL);
    pthread_join(t2[0], NULL);

    cout <<a<<" "<<b<<" "<< count;

    free(t1);
    free(t2);
    return 0;
}
//g++ -o a a.cpp -lpthread -lm -Wshadow -Wall -g  -fsaniti=address -fsanitize=undefined -D_GLIBCXX_DEBUG
