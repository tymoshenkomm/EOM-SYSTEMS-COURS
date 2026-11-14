#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <program> [args...]\n", argv[0]);
        return EXIT_FAILURE;
    }

    printf("Parent PID: %d\nCreating child...\n", getpid());
    fflush(stdout);

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        return EXIT_FAILURE;
    }

    if (pid == 0) {
        printf("Child PID: %d\nChild PPID: %d\nExecuting: %s\n", getpid(), getppid(), argv[1]);
        fflush(stdout);
        execvp(argv[1], &argv[1]);
        perror("execvp");
        _exit(EXIT_FAILURE);
    }

    int status;
    if (waitpid(pid, &status, 0) < 0) {
        perror("waitpid");
        return EXIT_FAILURE;
    }

    printf("Child %d completed\n", pid);
    if (WIFEXITED(status)) {
        printf("Exit status: %d\n", WEXITSTATUS(status));
    }
    printf("Parent continues\n");

    return EXIT_SUCCESS;
}
