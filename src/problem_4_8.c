#include <stdio.h>
#include <stdlib.h>

int binary_search(int *arr, int left, int right, int target) {
    int mid;

    if (left > right) {
        return -1;
    }

    mid = (left + right) / 2;

    if (arr[mid] == target) {
        return mid;
    }

    if (target < arr[mid]) {
        return binary_search(arr, left, mid - 1, target);
    }

    return binary_search(arr, mid + 1, right, target);
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
    int target;
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

    if (scanf("%d", &target) != 1) {
        free(arr);
        return 1;
    }

    printf("Sorted input array: ");
    print_array(arr, size);
    printf("Target: %d\n", target);
    printf("Binary search index: %d\n", binary_search(arr, 0, size - 1, target));

    free(arr);
    return 0;
}
