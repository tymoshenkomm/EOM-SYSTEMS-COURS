#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
pthread_mutex_t m1=PTHREAD_MUTEX_INITIALIZER,m2=PTHREAD_MUTEX_INITIALIZER;
void *w1(void *a){(void)a;printf("Thread 1: locking mutex1\n");pthread_mutex_lock(&m1);sleep(1);printf("Thread 1: locking mutex2\n");pthread_mutex_lock(&m2);printf("Thread 1: critical section\n");pthread_mutex_unlock(&m2);pthread_mutex_unlock(&m1);return NULL;}
void *w2(void *a){(void)a;printf("Thread 2: locking mutex1\n");pthread_mutex_lock(&m1);sleep(1);printf("Thread 2: locking mutex2\n");pthread_mutex_lock(&m2);printf("Thread 2: critical section\n");pthread_mutex_unlock(&m2);pthread_mutex_unlock(&m1);return NULL;}
int main(void){pthread_t t1,t2;pthread_create(&t1,NULL,w1,NULL);pthread_create(&t2,NULL,w2,NULL);pthread_join(t1,NULL);pthread_join(t2,NULL);return 0;}
