#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
void *calculate(void *arg){int v=*(int *)arg;int *r=malloc(sizeof(*r));if(!r)return NULL;*r=v*v;return r;}
int main(void){pthread_t t;int v=12;pthread_create(&t,NULL,calculate,&v);void *tr=NULL;pthread_join(t,&tr);if(tr){int *r=tr;printf("Result = %d\n",*r);free(r);}return 0;}
