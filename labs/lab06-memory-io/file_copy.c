#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define BUFFER_SIZE 4096
int main(int argc, char *argv[]) {
    if (argc != 3) { fprintf(stderr, "Usage: %s <source> <destination>\n", argv[0]); return 1; }
    int src = open(argv[1], O_RDONLY);
    if (src == -1) { perror("open source"); return 1; }
    int dst = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dst == -1) { perror("open destination"); close(src); return 1; }
    char buf[BUFFER_SIZE];
    ssize_t r;
    while ((r = read(src, buf, sizeof(buf))) > 0) {
        ssize_t tot = 0;
        while (tot < r) {
            ssize_t w = write(dst, buf + tot, (size_t)(r - tot));
            if (w == -1) { perror("write"); close(src); close(dst); return 1; }
            tot += w;
        }
    }
    if (r == -1) { perror("read"); close(src); close(dst); return 1; }
    if (close(src) == -1) { perror("close source"); close(dst); return 1; }
    if (close(dst) == -1) { perror("close destination"); return 1; }
    return 0;
}
