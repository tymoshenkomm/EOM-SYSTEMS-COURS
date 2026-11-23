#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
int main(void) {
    const char message[] = "Hello from write()\n";
    int fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) { perror("open"); return 1; }
    ssize_t written = write(fd, message, strlen(message));
    if (written == -1) { perror("write"); close(fd); return 1; }
    printf("Requested: %zu bytes\nWritten:   %zd bytes\n", strlen(message), written);
    if (close(fd) == -1) { perror("close"); return 1; }
    return 0;
}
