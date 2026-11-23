#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_LINE 1024
#define MAX_ARGS 64

static void parse_args(char *cmd, char **argv) {
    int i = 0;
    char *tok = strtok(cmd, " \t\r\n");
    while (tok && i < MAX_ARGS - 1) {
        argv[i++] = tok;
        tok = strtok(NULL, " \t\r\n");
    }
    argv[i] = NULL;
}

static void run_single(char *cmd) {
    char *outfile = NULL;
    char *gt = strchr(cmd, '>');
    if (gt) {
        *gt = '\0';
        outfile = strtok(gt + 1, " \t\r\n");
    }
    char *argv[MAX_ARGS];
    parse_args(cmd, argv);
    if (!argv[0][0]) return;
    if (strcmp(argv[0], "exit") == 0) exit(0);
    if (strcmp(argv[0], "cd") == 0) {
        const char *dir = argv[1] ? argv[1] : getenv("HOME");
        if (!dir || chdir(dir) == -1) perror("cd");
        return;
    }
    pid_t pid = fork();
    if (pid == -1) { perror("fork"); return; }
    if (pid == 0) {
        signal(SIGINT, SIG_DFL);
        if (outfile) {
            int fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd == -1) { perror("open"); _exit(1); }
            if (dup2(fd, STDOUT_FILENO) == -1) { perror("dup2"); close(fd); _exit(1); }
            close(fd);
        }
        execvp(argv[0], argv);
        perror("execvp");
        _exit(127);
    }
    if (waitpid(pid, NULL, 0) == -1) perror("waitpid");
}

static void run_pipe(char *left, char *right) {
    char *largv[MAX_ARGS], *rargv[MAX_ARGS];
    parse_args(left, largv);
    parse_args(right, rargv);
    if (!largv[0] || !rargv[0]) return;
    int pfd[2];
    if (pipe(pfd) == -1) { perror("pipe"); return; }
    pid_t c1 = fork();
    if (c1 == -1) { perror("fork"); close(pfd[0]); close(pfd[1]); return; }
    if (c1 == 0) {
        signal(SIGINT, SIG_DFL);
        if (dup2(pfd[1], STDOUT_FILENO) == -1) { perror("dup2"); _exit(1); }
        close(pfd[0]); close(pfd[1]);
        execvp(largv[0], largv);
        perror("execvp"); _exit(127);
    }
    pid_t c2 = fork();
    if (c2 == -1) { perror("fork"); close(pfd[0]); close(pfd[1]); waitpid(c1, NULL, 0); return; }
    if (c2 == 0) {
        signal(SIGINT, SIG_DFL);
        if (dup2(pfd[0], STDIN_FILENO) == -1) { perror("dup2"); _exit(1); }
        close(pfd[0]); close(pfd[1]);
        execvp(rargv[0], rargv);
        perror("execvp"); _exit(127);
    }
    close(pfd[0]); close(pfd[1]);
    waitpid(c1, NULL, 0);
    waitpid(c2, NULL, 0);
}

int main(void) {
    struct sigaction sa = {0};
    sa.sa_handler = SIG_IGN;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGINT, &sa, NULL);
    char line[MAX_LINE];
    while (1) {
        printf("myshell> ");
        fflush(stdout);
        if (!fgets(line, sizeof(line), stdin)) { printf("\n"); break; }
        char *bar = strchr(line, '|');
        if (bar) { *bar = '\0'; run_pipe(line, bar + 1); }
        else run_single(line);
    }
    return 0;
}
