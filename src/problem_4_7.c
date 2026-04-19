#include <stdio.h>
#include <stdlib.h>

int array_max(int *arr, int size) {
    int max_of_rest;

    if (size == 1) {
        return arr[0];
    }

    max_of_rest = array_max(arr, size - 1);
    return arr[size - 1] > max_of_rest ? arr[size - 1] : max_of_rest;
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
    printf("Maximum element: %d\n", array_max(arr, size));

    free(arr);
    return 0;
}
