#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
typedef struct{int value;}SharedData;
void *worker(void *arg){SharedData *data=arg;data->value+=10;printf("Worker: value=%d address=%p\n",data->value,(void *)data);return NULL;}
int main(void){SharedData *data=malloc(sizeof(*data));if(!data)return 1;data->value=100;pthread_t t;pthread_create(&t,NULL,worker,data);pthread_join(t,NULL);printf("Main: value=%d address=%p\n",data->value,(void *)data);free(data);return 0;}
