#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int global_value = 10;
int main(void) {
    int local = 20;
    int *dynamic = malloc(sizeof(*dynamic));
    if (!dynamic) { perror("malloc"); return 1; }
    *dynamic = 30;
    printf("PID:    %d\nmain:   %p\nglobal: %p\nheap:   %p\nstack:  %p\n", getpid(), (void *)main, (void *)&global_value, (void *)dynamic, (void *)&local);
    fflush(stdout);
    sleep(60);
    free(dynamic);
    return 0;
}
