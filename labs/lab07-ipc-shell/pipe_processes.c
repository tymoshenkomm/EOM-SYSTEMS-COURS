#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
int main(void) {
    int pipefd[2];
    if (pipe(pipefd) == -1) { perror("pipe"); return 1; }
    pid_t pid = fork();
    if (pid == -1) { perror("fork"); return 1; }
    if (pid == 0) {
        close(pipefd[1]);
        char buf[128];
        ssize_t n = read(pipefd[0], buf, sizeof(buf) - 1);
        if (n == -1) { perror("read"); exit(1); }
        buf[n] = 0;
        printf("Child received: %s", buf);
        close(pipefd[0]);
        exit(0);
    }
    close(pipefd[0]);
    const char msg[] = "Message from parent\n";
    if (write(pipefd[1], msg, strlen(msg)) == -1) perror("write");
    close(pipefd[1]);
    waitpid(pid, NULL, 0);
    return 0;
}
