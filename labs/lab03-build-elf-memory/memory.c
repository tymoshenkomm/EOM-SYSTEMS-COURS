#include <stdio.h>
#include <stdlib.h>
int global_initialized = 10;
int global_uninitialized;
static int static_initialized = 20;
static int static_uninitialized;
int main(void) {
    int local = 30;
    int *dynamic = malloc(sizeof(int));
    if (!dynamic) return 1;
    *dynamic = 40;
    printf("main: %p\nglob_init: %p\nglob_uninit: %p\nstat_init: %p\nstat_uninit: %p\nlocal: %p\ndynamic: %p\n", (void*)main, (void*)&global_initialized, (void*)&global_uninitialized, (void*)&static_initialized, (void*)&static_uninitialized, (void*)&local, (void*)dynamic);
    free(dynamic);
    return 0;
}
