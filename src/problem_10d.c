#include <stdio.h>
#include <stdlib.h>

static int max_int(int a, int b) {
    return a > b ? a : b;
}

static int string_length(const char *str) {
    int length = 0;

    while (str[length] != '\0') {
        length++;
    }

    return length;
}

int lcs(char *s1, char *s2, int m, int n) {
    int **dp = (int **)malloc((size_t)(m + 1) * sizeof(int *));
    int result;

    if (dp == NULL) {
        exit(1);
    }

    for (int i = 0; i <= m; i++) {
        dp[i] = (int *)calloc((size_t)(n + 1), sizeof(int));
        if (dp[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(dp[j]);
            }
            free(dp);
            exit(1);
        }
    }

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = max_int(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    result = dp[m][n];

    for (int i = 0; i <= m; i++) {
        free(dp[i]);
    }
    free(dp);

    return result;
}

static void print_lcs_string(char *s1, char *s2, int m, int n) {
    int **dp = (int **)malloc((size_t)(m + 1) * sizeof(int *));
    int length;
    char *sequence;

    if (dp == NULL) {
        exit(1);
    }

    for (int i = 0; i <= m; i++) {
        dp[i] = (int *)calloc((size_t)(n + 1), sizeof(int));
        if (dp[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(dp[j]);
            }
            free(dp);
            exit(1);
        }
    }

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = max_int(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    length = dp[m][n];
    sequence = (char *)malloc((size_t)length + 1);
    if (sequence == NULL) {
        for (int i = 0; i <= m; i++) {
            free(dp[i]);
        }
        free(dp);
        exit(1);
    }

    sequence[length] = '\0';

    for (int i = m, j = n; i > 0 && j > 0;) {
        if (s1[i - 1] == s2[j - 1]) {
            sequence[--length] = s1[i - 1];
            i--;
            j--;
        } else if (dp[i - 1][j] >= dp[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }

    printf("LCS string: %s\n", sequence);

    free(sequence);
    for (int i = 0; i <= m; i++) {
        free(dp[i]);
    }
    free(dp);
}

int main(void) {
    char s1[256];
    char s2[256];
    int m;
    int n;

    if (scanf("%255s %255s", s1, s2) != 2) {
        return 1;
    }

    m = string_length(s1);
    n = string_length(s2);

    printf("Raw input first string: %s\n", s1);
    printf("Raw input second string: %s\n", s2);
    printf("Expected output (LCS length): %d\n", lcs(s1, s2, m, n));
    print_lcs_string(s1, s2, m, n);

    return 0;
}
