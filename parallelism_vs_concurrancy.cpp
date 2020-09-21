#include<bits/stdc++.h>
#include <unistd.h>
#include <pthread.h>
using namespace std;
int ans=0;
const int MAX=1e7;
parallelism :
    -->two threads are doing the work at the 
       exactly same time.
    -->Need some kind of harware support like multicore

Concurrancy
    --> Fast Context switching 
https://medium.com/@itIsMadhavan/concurrency-vs-parallelism-a-brief-review-b337c8dac350

static pthread_mutex_t mutex1= PTHREAD_MUTEX_INITIALIZER; 
void* fx(void* arg)
{
    for(int i=0;i<MAX;i++)
    {
        pthread_mutex_lock(&mutex1);
        ans++;
        pthread_mutex_unlock(&mutex1);
    }
    return NULL;
}
int main(int argc, char **argv)
{
    clock_t tStart = clock();
    pthread_t t1,t2;
    pthread_create(&t1,NULL,fx,NULL);
    pthread_create(&t2,NULL,fx,NULL);
    //fx();
    pthread_join(t2,NULL);
    pthread_join(t1,NULL);
    cout<<ans<<"\n";
    cout<<fixed<<setprecision(5)<<"\nTime taken: "<<(double)(clock() - tStart)/CLOCKS_PER_SEC;
    return 0;
}
//g++ -o a a.cpp -lpthread -lm -Wshadow -Wall -g  -fsaniti=address -fsanitize=undefined -D_GLIBCXX_DEBUG