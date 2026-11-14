#include <stdio.h>
#include <unistd.h>
int main(void) {
    printf("PID:  %d\nPPID: %d\n", getpid(), getppid());
    sleep(30);
    return 0;
}
