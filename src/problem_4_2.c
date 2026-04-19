#include <stdio.h>

long long fibonacci(int n) {
    if (n <= 1) {
        return n;
    }

    return fibonacci(n - 1) + fibonacci(n - 2);
}

int main(void) {
    int n;

    if (scanf("%d", &n) != 1 || n < 0) {
        return 1;
    }

    printf("Raw input n: %d\n", n);
    printf("Fibonacci: %lld\n", fibonacci(n));

    return 0;
}
