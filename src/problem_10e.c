#include <stdio.h>
#include <stdlib.h>

int lis(int *arr, int n) {
    int *dp = (int *)malloc((size_t)n * sizeof(int));
    int best = 1;

    if (dp == NULL) {
        exit(1);
    }

    for (int i = 0; i < n; i++) {
        dp[i] = 1;
    }

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (arr[j] < arr[i] && dp[j] + 1 > dp[i]) {
                dp[i] = dp[j] + 1;
            }
        }
        if (dp[i] > best) {
            best = dp[i];
        }
    }

    free(dp);
    return best;
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
    int *arr;

    if (scanf("%d", &n) != 1 || n <= 0) {
        return 1;
    }

    arr = (int *)malloc((size_t)n * sizeof(int));
    if (arr == NULL) {
        return 1;
    }

    for (int i = 0; i < n; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            free(arr);
            return 1;
        }
    }

    printf("Raw input array: ");
    print_array(arr, n);
    printf("Expected output (LIS length): %d\n", lis(arr, n));

    free(arr);
    return 0;
}
