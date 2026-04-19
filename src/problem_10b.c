#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int min_coins(int *coins, int n, int amount) {
    int *dp = (int *)malloc((size_t)(amount + 1) * sizeof(int));
    int answer;

    if (dp == NULL) {
        exit(1);
    }

    dp[0] = 0;
    for (int i = 1; i <= amount; i++) {
        dp[i] = INT_MAX / 2;
    }

    for (int current = 1; current <= amount; current++) {
        for (int i = 0; i < n; i++) {
            if (coins[i] <= current && dp[current - coins[i]] + 1 < dp[current]) {
                dp[current] = dp[current - coins[i]] + 1;
            }
        }
    }

    answer = (dp[amount] >= INT_MAX / 4) ? -1 : dp[amount];
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
    printf("Expected output (minimum number of coins): %d\n", min_coins(coins, n, amount));

    free(coins);
    return 0;
}
