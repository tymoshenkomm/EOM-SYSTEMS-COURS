#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
static volatile sig_atomic_t got_term = 0;
static void handle_sigterm(int sig) {
    (void)sig;
    const char msg[] = "Child caught SIGTERM gracefully\n";
    write(STDOUT_FILENO, msg, sizeof(msg) - 1);
    got_term = 1;
}
int main(void) {
    pid_t pid = fork();
    if (pid == -1) { perror("fork"); return 1; }
    if (pid == 0) {
        struct sigaction sa = {0};
        sa.sa_handler = handle_sigterm;
        sigemptyset(&sa.sa_mask);
        sigaction(SIGTERM, &sa, NULL);
        while (!got_term) pause();
        _exit(0);
    }
    sleep(1);
    printf("Parent sending SIGTERM to child %d\n", pid);
    kill(pid, SIGTERM);
    int status;
    waitpid(pid, &status, 0);
    if (WIFEXITED(status)) printf("Child exited with status %d\n", WEXITSTATUS(status));
    return 0;
}
