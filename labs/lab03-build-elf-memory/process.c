#include <stdio.h>
#include <unistd.h>
int main(void) {
    printf("PID: %d\nProcess is running...\n", getpid());
    sleep(1);
    return 0;
}
