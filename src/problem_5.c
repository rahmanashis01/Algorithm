#include <stdio.h>
#include <stdlib.h>

void merge(int *arr, int left, int mid, int right) {
    int size = right - left + 1;
    int *temp = (int *)malloc((size_t)size * sizeof(int));
    int i = left;
    int j = mid + 1;
    int k = 0;

    if (temp == NULL) {
        exit(1);
    }

    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }

    while (i <= mid) {
        temp[k++] = arr[i++];
    }

    while (j <= right) {
        temp[k++] = arr[j++];
    }

    for (i = 0; i < size; i++) {
        arr[left + i] = temp[i];
    }

    free(temp);
}

void merge_sort(int *arr, int left, int right) {
    int mid;

    if (left >= right) {
        return;
    }

    mid = left + (right - left) / 2;
    merge_sort(arr, left, mid);
    merge_sort(arr, mid + 1, right);
    merge(arr, left, mid, right);
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

    merge_sort(arr, 0, size - 1);

    printf("Expected output (merge sorted array): ");
    print_array(arr, size);

    free(arr);
    return 0;
}
