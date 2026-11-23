#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
int main(void) {
    int pipefd[2];
    if (pipe(pipefd) == -1) { perror("pipe"); return 1; }
    pid_t c1 = fork();
    if (c1 == 0) {
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[0]); close(pipefd[1]);
        char *args[] = {"ls", "-l", NULL};
        execvp(args[0], args);
        perror("execvp ls"); _exit(1);
    }
    pid_t c2 = fork();
    if (c2 == 0) {
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]); close(pipefd[1]);
        char *args[] = {"wc", "-l", NULL};
        execvp(args[0], args);
        perror("execvp wc"); _exit(1);
    }
    close(pipefd[0]); close(pipefd[1]);
    waitpid(c1, NULL, 0);
    waitpid(c2, NULL, 0);
    return 0;
}
