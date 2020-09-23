#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <math.h>
#include <pthread.h>
#include <semaphore.h>

using namespace std;

static pthread_mutex_t mutex1 = PTHREAD_ERRORCHECK_MUTEX_INITIALIZER_NP;
static pthread_mutex_t mutex2 = PTHREAD_ERRORCHECK_MUTEX_INITIALIZER_NP;
// sem_t mutex;
void *fx(void *args)
{
    if (*(int *)args == 2)
        sleep(1);
    if (*(int *)args == 1)
        printf("%d %d\n", *(int *)args, pthread_mutex_lock(&mutex1));
    if (*(int *)args == 2)
        printf("%d %d\n", *(int *)args, pthread_mutex_lock(&mutex2));
    printf("%d\n", *(int *)args);

    while (pthread_mutex_unlock(&mutex1) != 0)
        ;
    while (pthread_mutex_unlock(&mutex2) != 0)
        ;

    return NULL;
}
int main(int argc, char **argv)
{
    pthread_t t1, t2;

    //sem_init(&mutex, 0, 1);
    //sem_init(&db, 0, 1);

    int x1 = 1, x2 = 2, x3 = 2;
    pthread_create(&t1, NULL, fx, &x1);
    pthread_create(&t2, NULL, fx, &x2);

    //fx(&x3);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    return 0;
}
// #include <stdio.h>
// #include <iostream>
// #include <stdlib.h>
// #include <assert.h>
// #include <unistd.h>
// #include <math.h>
// #include <pthread.h>
// #include <semaphore.h>

// using namespace std;

// //First readers-writers problem

// int readers = 0;
// sem_t mutex, db ;

// void *reader(void *args)
// {
//     for (int i = 1; i <= 10000; i++)
//     {
//         sem_wait(&mutex);//Ensure that no other
//                         //reader can execute the <Entry> section while you are in it

//         /*<CRITICAL SECTION>*/

//         readers++;

//         cout << "Reader " << i << " in Database with " << readers << " readers\n";

//         if(readers==1)
//             sem_wait(&db);//If you are the first reader,
//                           //lock the resource from writers.
//                           // Resource stays reserved for subsequent readers

//         /*<EXIT CRITICAL SECTION>*/

//         sem_post(&mutex);   //Release

//         // Do the reading

//         sem_wait(&mutex);  //Ensure that no other
//                            //reader can execute the <Exit> section while
//                            //you are in it
//         /*<CRITICAL SECTION>*/

//         readers--;//Indicate that you are no longer
//                   //needing the shared resource. One fewer reader

//         if (readers == 0)//Checks if you are the last (only) reader
//                               //who is reading the shared file
//             sem_post(&db);//If you are last reader, then you can unlock the
//                           //resource. This makes it available to writers.

//         /*<EXIT CRITICAL SECTION>*/

//         sem_post(&mutex);   //Release
//     }
//     return NULL;
// }
// void *writer(void *args)
// {
//     for (int i = 1; i <= 100; i++)
//     {
//         sem_wait(&db); //Lock the shared file for a writer

//         /*<CRITICAL SECTION>*/

//         cout << "\t\t\t\t\tWriter " << i << " and "<<readers<<" readers in Database \n";

//         /*<EXIT CRITICAL SECTION>*/

//         sem_post(&db); //Release the shared file for use by other readers.
//                        //Writers are allowed if there are no readers requesting it.

//     }
//     return NULL;
// }
// int main(int argc, char **argv)
// {
//     pthread_t t1, t2;

//     sem_init(&mutex, 0, 1);
//     sem_init(&db, 0, 1);

//     pthread_create(&t1, NULL, reader, NULL);
//     pthread_create(&t2, NULL, writer, NULL);

//     pthread_join(t1, NULL);
//     pthread_join(t2, NULL);
//     return 0;
// }
