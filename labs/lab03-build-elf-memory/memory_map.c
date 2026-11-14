#include <stdio.h>
#include <stdlib.h>
int g_init = 1;
int g_uninit;
static int s_init = 2;
static int s_uninit;
const char *str_lit = "Hello ELF";
void sample_func(void) {}
int main(void) {
    int local_var = 3;
    int *heap_var = malloc(sizeof(int));
    if (!heap_var) return 1;
    *heap_var = 4;
    printf("Code/function:        %p\nString literal:       %p\nGlobal initialized:   %p\nStatic initialized:   %p\nGlobal uninitialized: %p\nStatic uninitialized: %p\nHeap allocation:      %p\nStack/local:          %p\n", (void*)sample_func, (void*)str_lit, (void*)&g_init, (void*)&s_init, (void*)&g_uninit, (void*)&s_uninit, (void*)heap_var, (void*)&local_var);
    free(heap_var);
    return 0;
}
