#include <stdio.h>

int count_digits(int n) {
    if (n < 10) {
        return 1;
    }

    return 1 + count_digits(n / 10);
}

int main(void) {
    int n;

    if (scanf("%d", &n) != 1 || n < 0) {
        return 1;
    }

    printf("Raw input n: %d\n", n);
    printf("Digit count: %d\n", count_digits(n));

    return 0;
}
