#include <stdio.h>
#include <stdlib.h>
int main(void) {
    int *a = malloc(sizeof(int)), *b = malloc(sizeof(int)), *c = malloc(sizeof(int));
    if (!a || !b || !c) return 1;
    printf("a: %p\nb: %p\nc: %p\n", (void*)a, (void*)b, (void*)c);
    free(a); free(b); free(c);
    return 0;
}
