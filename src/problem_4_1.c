#include <stdio.h>

long long factorial(int n) {
    long long result = 1;

    for (int i = 2; i <= n; i++) {
        result *= i;
    }

    return result;
}

int main(void) {
    int n;

    if (scanf("%d", &n) != 1 || n < 0) {
        return 1;
    }

    printf("Raw input n: %d\n", n);
    printf("Factorial: %lld\n", factorial(n));

    return 0;
}
