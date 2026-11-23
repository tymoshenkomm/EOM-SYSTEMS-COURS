#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define N 1000000L
#define THREAD_COUNT 4
typedef struct{int id;long start,end,result;}Task;
void *calculate_sum(void *arg){Task *t=arg;long s=0;for(long i=t->start;i<=t->end;i++)s+=i;t->result=s;return NULL;}
int main(void){pthread_t th[THREAD_COUNT];Task tk[THREAD_COUNT];long c=N/THREAD_COUNT;
for(int i=0;i<THREAD_COUNT;i++){tk[i]=(Task){i+1,i*c+1,(i==THREAD_COUNT-1)?N:(i+1)*c,0};pthread_create(&th[i],NULL,calculate_sum,&tk[i]);}
long tot=0;for(int i=0;i<THREAD_COUNT;i++){pthread_join(th[i],NULL);printf("Thread %d: %ld\n",tk[i].id,tk[i].result);tot+=tk[i].result;}
long exp=N*(N+1)/2;printf("\nParallel result: %ld\nExpected result: %ld\n\nCorrect: %s\n",tot,exp,(tot==exp)?"YES":"NO");return 0;}
