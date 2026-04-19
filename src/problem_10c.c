#include <stdio.h>
#include <stdlib.h>

int count_ways(int *coins, int n, int amount) {
    int *dp = (int *)calloc((size_t)(amount + 1), sizeof(int));
    int answer;

    if (dp == NULL) {
        exit(1);
    }

    dp[0] = 1;

    for (int i = 0; i < n; i++) {
        for (int current = coins[i]; current <= amount; current++) {
            dp[current] += dp[current - coins[i]];
        }
    }

    answer = dp[amount];
    free(dp);
    return answer;
}

static void print_array(const int *arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d", arr[i]);
        if (i < size - 1) {
            printf(" ");
        }
    }
    printf("\n");
}

int main(void) {
    int n;
    int amount;
    int *coins;

    if (scanf("%d", &n) != 1 || n <= 0) {
        return 1;
    }

    coins = (int *)malloc((size_t)n * sizeof(int));
    if (coins == NULL) {
        return 1;
    }

    for (int i = 0; i < n; i++) {
        if (scanf("%d", &coins[i]) != 1 || coins[i] <= 0) {
            free(coins);
            return 1;
        }
    }

    if (scanf("%d", &amount) != 1 || amount < 0) {
        free(coins);
        return 1;
    }

    printf("Raw input coins: ");
    print_array(coins, n);
    printf("Amount: %d\n", amount);
    printf("Expected output (number of combinations): %d\n", count_ways(coins, n, amount));

    free(coins);
    return 0;
}
