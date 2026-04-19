#include <stdio.h>

double power(double base, int exp) {
    if (exp == 0) {
        return 1.0;
    }

    return base * power(base, exp - 1);
}

int main(void) {
    double base;
    int exp;

    if (scanf("%lf %d", &base, &exp) != 2 || exp < 0) {
        return 1;
    }

    printf("Raw input base: %.10g\n", base);
    printf("Raw input exp: %d\n", exp);
    printf("Power: %.10g\n", power(base, exp));

    return 0;
}
