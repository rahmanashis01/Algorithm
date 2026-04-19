#include <stdio.h>
#include <stdlib.h>

int knapsack_01(int *weights, int *values, int n, int W) {
    int **dp = (int **)malloc((size_t)(n + 1) * sizeof(int *));
    int result;

    if (dp == NULL) {
        exit(1);
    }

    for (int i = 0; i <= n; i++) {
        dp[i] = (int *)calloc((size_t)(W + 1), sizeof(int));
        if (dp[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(dp[j]);
            }
            free(dp);
            exit(1);
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            dp[i][w] = dp[i - 1][w];
            if (weights[i - 1] <= w) {
                int take = dp[i - 1][w - weights[i - 1]] + values[i - 1];
                if (take > dp[i][w]) {
                    dp[i][w] = take;
                }
            }
        }
    }

    result = dp[n][W];

    for (int i = 0; i <= n; i++) {
        free(dp[i]);
    }
    free(dp);

    return result;
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
    int W;
    int *weights;
    int *values;

    if (scanf("%d", &n) != 1 || n <= 0) {
        return 1;
    }

    weights = (int *)malloc((size_t)n * sizeof(int));
    values = (int *)malloc((size_t)n * sizeof(int));
    if (weights == NULL || values == NULL) {
        free(weights);
        free(values);
        return 1;
    }

    for (int i = 0; i < n; i++) {
        if (scanf("%d", &weights[i]) != 1 || weights[i] <= 0) {
            free(weights);
            free(values);
            return 1;
        }
    }

    for (int i = 0; i < n; i++) {
        if (scanf("%d", &values[i]) != 1 || values[i] < 0) {
            free(weights);
            free(values);
            return 1;
        }
    }

    if (scanf("%d", &W) != 1 || W < 0) {
        free(weights);
        free(values);
        return 1;
    }

    printf("Raw input weights: ");
    print_array(weights, n);
    printf("Raw input values: ");
    print_array(values, n);
    printf("Capacity: %d\n", W);
    printf("Expected output (maximum knapsack value): %d\n", knapsack_01(weights, values, n, W));

    free(weights);
    free(values);
    return 0;
}
