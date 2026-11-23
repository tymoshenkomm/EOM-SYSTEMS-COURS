#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main(void) {
    const size_t size = 100 * 1024 * 1024;
    printf("PID: %d\n", getpid());
    char *memory = malloc(size);
    if (!memory) { perror("malloc"); return 1; }
    printf("Allocated %zu bytes\nAddress: %p\nPress Enter to touch memory...\n", size, (void *)memory);
    fflush(stdout);
    getchar();
    for (size_t i = 0; i < size; i += 4096) memory[i] = 1;
    printf("Memory touched. Press Enter to exit...\n");
    fflush(stdout);
    getchar();
    free(memory);
    return 0;
}
