#include <stdio.h>

static void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

static void sort_array(int *arr, int size) {
    for (int i = 0; i < size - 1; i++) {
        int min_index = i;

        for (int j = i + 1; j < size; j++) {
            if (arr[j] < arr[min_index]) {
                min_index = j;
            }
        }

        if (min_index != i) {
            swap(&arr[i], &arr[min_index]);
        }
    }
}

static int find_median(const int *arr, int size) {
    int target_index = (size - 1) / 2;

    return arr[target_index];
}

int main(void) {
    int size;

    if (scanf("%d", &size) != 1 || size <= 0) {
        return 1;
    }

    int arr[size];

    for (int i = 0; i < size; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            return 1;
        }
    }

    sort_array(arr, size);

    printf("Sorted input: ");
    for (int i = 0; i < size; i++) {
        printf("%d", arr[i]);
        if (i < size - 1) {
            printf(" ");
        }
    }
    printf("\n");

    printf("Median: %d\n", find_median(arr, size));
    return 0;
}
