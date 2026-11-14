#include <stdio.h>

int compute_score(int a, int b)
{
    int base;
    if (a > b) {
        base = a - b;
    } else {
        base = a + b;
    }

    for (int i = 0; i < 3; i++) {
        base += i;
    }

    return base;
}

int main(void)
{
    int res = compute_score(10, 4);
    printf("Score: %d\n", res);
    return 0;
}
