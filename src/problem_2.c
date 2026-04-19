#include <stdio.h>
#include <stdlib.h>

static void copy_array(int *dest, const int *src, int size) {
    for (int i = 0; i < size; i++) {
        dest[i] = src[i];
    }
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

static int compare_desc(const void *a, const void *b) {
    int left = *(const int *)a;
    int right = *(const int *)b;

    return (right > left) - (right < left);
}

int find_kth_largest(int *arr, int size, int k) {
    for (int pass = 0; pass < k; pass++) {
        int swapped = 0;

        for (int i = 0; i < size - 1 - pass; i++) {
            if (arr[i] > arr[i + 1]) {
                int temp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = temp;
                swapped = 1;
            }
        }

        if (!swapped) {
            break;
        }
    }

    return arr[size - k];
}

int main(void) {
    int size;
    int k;

    if (scanf("%d", &size) != 1 || size <= 0) {
        return 1;
    }

    int *arr = (int *)malloc((size_t)size * sizeof(int));
    int *working = (int *)malloc((size_t)size * sizeof(int));
    int *sorted = (int *)malloc((size_t)size * sizeof(int));

    if (arr == NULL || working == NULL || sorted == NULL) {
        free(arr);
        free(working);
        free(sorted);
        return 1;
    }

    for (int i = 0; i < size; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            free(arr);
            free(working);
            free(sorted);
            return 1;
        }
    }

    if (scanf("%d", &k) != 1 || k < 1 || k > size) {
        free(arr);
        free(working);
        free(sorted);
        return 1;
    }

    copy_array(working, arr, size);
    copy_array(sorted, arr, size);

    int kth_largest = find_kth_largest(working, size, k);
    qsort(sorted, (size_t)size, sizeof(int), compare_desc);

    printf("Raw input: ");
    print_array(arr, size);

    printf("Sorted descending: ");
    print_array(sorted, size);

    printf("K-th largest element (k = %d): %d\n", k, kth_largest);

    free(arr);
    free(working);
    free(sorted);
    return 0;
}
