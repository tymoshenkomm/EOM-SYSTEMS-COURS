#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define ITERATIONS 1000000
long counter=0;
pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
void *increment(void *arg){(void)arg;for(long i=0;i<ITERATIONS;i++){pthread_mutex_lock(&mutex);counter++;pthread_mutex_unlock(&mutex);}return NULL;}
int main(void){pthread_t t1,t2;pthread_create(&t1,NULL,increment,NULL);pthread_create(&t2,NULL,increment,NULL);pthread_join(t1,NULL);pthread_join(t2,NULL);printf("Expected: %ld\nActual:   %ld\n",2L*ITERATIONS,counter);pthread_mutex_destroy(&mutex);return EXIT_SUCCESS;}
