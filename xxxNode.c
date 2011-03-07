/***************************************************
* xxxNode.c
* By MikeRoguez
* 	genera Publisher y Subscribers en un solo
* 	proceso multihilo con pthreads.
* 7/marzo/2011
****************************************************/

#include <time.h>
#include <stdio.h>
#include <pthread.h> 
#include <errno.h>
#include <stdlib.h>
#include "/home/partikle/user/uDDS/include/Data.h"
#include "/home/partikle/user/uDDS/include/uDDS.h"

pthread_mutex_t rw_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t reader_mutex = PTHREAD_MUTEX_INITIALIZER;
int num_readers = 0;

int main()  
{
  pthread_t subscriber_thread1; 
  pthread_t publisher_thread1; 
  void *publish();
  void *subscribe();

    pthread_create(&subscriber_thread1,NULL,subscribe,NULL);
    pthread_create(&publisher_thread1,NULL,subscribe,NULL);
    pthread_join(subscriber_thread1,NULL);
    pthread_join(publisher_thread1,NULL);

}

void *subscribe()
{
  struct timespec t;
  int i = 0;
  while  (1) {
    pthread_mutex_lock(&reader_mutex);
    num_readers++;
    if (num_readers == 1) pthread_mutex_lock(&rw_mutex);
    pthread_mutex_unlock(&reader_mutex);

    printf("start reading\n");
    t.tv_sec = 0;
    t.tv_nsec = 1;
    nanosleep (&t, 0);  
    printf("finish reading\n");

    pthread_mutex_lock(&reader_mutex);
    num_readers--;
    if (num_readers == 0) pthread_mutex_unlock(&rw_mutex);
    pthread_mutex_unlock(&reader_mutex);
    t.tv_sec = 0;
    t.tv_nsec = i%3;
    nanosleep (&t, 0);    
    i++;
  }
  pthread_exit(NULL);
}

void *publish()
{ int i;
  struct timespec t;
  for (i=0;i<100;i++) {
    pthread_mutex_lock(&rw_mutex);
    printf("start writing \n");
    t.tv_sec = 0;
    t.tv_nsec = 1;
    nanosleep (&t, 0);
    printf("finish writing \n");
    pthread_mutex_unlock(&rw_mutex);
    t.tv_sec = 0;
    t.tv_nsec = i%2;
    nanosleep (&t, 0);
  }
  pthread_exit(NULL);
}
 
