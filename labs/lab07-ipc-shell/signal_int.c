#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
static void handle_sigint(int sig) {
    (void)sig;
    const char msg[] = "\nSIGINT received\n";
    write(STDOUT_FILENO, msg, sizeof(msg) - 1);
}
int main(void) {
    struct sigaction sa = {0};
    sa.sa_handler = handle_sigint;
    sigemptyset(&sa.sa_mask);
    if (sigaction(SIGINT, &sa, NULL) == -1) return 1;
    while (1) pause();
    return 0;
}
