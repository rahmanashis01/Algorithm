#include <stdio.h>
#include <stdlib.h>

static int swap_count = 0;

static void swap(int *a, int *b) {
    int temp;

    if (a == b) {
        return;
    }

    temp = *a;
    *a = *b;
    *b = temp;
    swap_count++;
}

int partition(int *arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }

    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

void quick_sort(int *arr, int low, int high) {
    int pivot_index;

    if (low >= high) {
        return;
    }

    pivot_index = partition(arr, low, high);
    quick_sort(arr, low, pivot_index - 1);
    quick_sort(arr, pivot_index + 1, high);
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
    int size;
    int *arr;

    if (scanf("%d", &size) != 1 || size <= 0) {
        return 1;
    }

    arr = (int *)malloc((size_t)size * sizeof(int));
    if (arr == NULL) {
        return 1;
    }

    for (int i = 0; i < size; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            free(arr);
            return 1;
        }
    }

    printf("Raw input array: ");
    print_array(arr, size);

    quick_sort(arr, 0, size - 1);

    printf("Expected output (quick sorted array): ");
    print_array(arr, size);
    printf("Total swaps: %d\n", swap_count);

    free(arr);
    return 0;
}
