#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
int main(void) {
    pid_t pid = fork();
    if (pid == -1) { perror("fork"); return 1; }
    if (pid == 0) {
        int fd = open("ls-output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd == -1) { perror("open"); _exit(1); }
        if (dup2(fd, STDOUT_FILENO) == -1) { perror("dup2"); close(fd); _exit(1); }
        close(fd);
        char *args[] = {"ls", "-l", NULL};
        execvp(args[0], args);
        perror("execvp"); _exit(1);
    }
    waitpid(pid, NULL, 0);
    return 0;
}
