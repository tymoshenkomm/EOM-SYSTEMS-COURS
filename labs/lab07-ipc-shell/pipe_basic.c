#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
int main(void) {
    int pipefd[2];
    if (pipe(pipefd) == -1) { perror("pipe"); return 1; }
    printf("Read end:  %d\nWrite end: %d\n", pipefd[0], pipefd[1]);
    const char msg[] = "Hello through pipe!\n";
    if (write(pipefd[1], msg, strlen(msg)) == -1) { perror("write"); return 1; }
    char buf[128];
    ssize_t n = read(pipefd[0], buf, sizeof(buf) - 1);
    if (n == -1) { perror("read"); return 1; }
    buf[n] = 0;
    printf("Received: %s", buf);
    close(pipefd[0]); close(pipefd[1]);
    return 0;
}
