#include <stdio.h>
#include <stdlib.h>

static void print_array(const int *arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d", arr[i]);
        if (i < size - 1) {
            printf(" ");
        }
    }
    printf("\n");
}

static void insert_sorted(int *out, int current_size, int value) {
    int i = current_size - 1;

    while (i >= 0 && out[i] > value) {
        out[i + 1] = out[i];
        i--;
    }

    out[i + 1] = value;
}

void merge_sorted(int *a, int n, int *b, int m, int *out) {
    int out_size = 0;

    for (int i = 0; i < n; i++) {
        insert_sorted(out, out_size, a[i]);
        out_size++;
    }

    for (int i = 0; i < m; i++) {
        insert_sorted(out, out_size, b[i]);
        out_size++;
    }
}

int main(void) {
    int n;
    int m;

    if (scanf("%d", &n) != 1 || n < 0) {
        return 1;
    }

    int *a = NULL;
    if (n > 0) {
        a = (int *)malloc((size_t)n * sizeof(int));
        if (a == NULL) {
            return 1;
        }
    }

    for (int i = 0; i < n; i++) {
        if (scanf("%d", &a[i]) != 1) {
            free(a);
            return 1;
        }
    }

    if (scanf("%d", &m) != 1 || m < 0) {
        free(a);
        return 1;
    }

    int *b = NULL;
    if (m > 0) {
        b = (int *)malloc((size_t)m * sizeof(int));
        if (b == NULL) {
            free(a);
            return 1;
        }
    }

    for (int i = 0; i < m; i++) {
        if (scanf("%d", &b[i]) != 1) {
            free(a);
            free(b);
            return 1;
        }
    }

    int total = n + m;
    int *out = NULL;
    if (total > 0) {
        out = (int *)malloc((size_t)total * sizeof(int));
        if (out == NULL) {
            free(a);
            free(b);
            return 1;
        }
    }

    merge_sorted(a, n, b, m, out);

    printf("Raw input A: ");
    print_array(a, n);

    printf("Raw input B: ");
    print_array(b, m);

    printf("Merged sorted output: ");
    print_array(out, total);

    free(a);
    free(b);
    free(out);
    return 0;
}
