#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int weight;
    int value;
} Item;

static double ratio(const Item *item) {
    return (double)item->value / (double)item->weight;
}

static void swap_items(Item *a, Item *b) {
    Item temp = *a;
    *a = *b;
    *b = temp;
}

static void sort_by_ratio_desc(Item *items, int n) {
    for (int i = 0; i < n - 1; i++) {
        int best = i;

        for (int j = i + 1; j < n; j++) {
            if (ratio(&items[j]) > ratio(&items[best])) {
                best = j;
            }
        }

        if (best != i) {
            swap_items(&items[i], &items[best]);
        }
    }
}

double fractional_knapsack(Item *items, int n, int capacity) {
    double total_value = 0.0;
    int remaining = capacity;

    sort_by_ratio_desc(items, n);

    for (int i = 0; i < n && remaining > 0; i++) {
        if (items[i].weight <= remaining) {
            total_value += items[i].value;
            remaining -= items[i].weight;
        } else {
            total_value += ratio(&items[i]) * remaining;
            remaining = 0;
        }
    }

    return total_value;
}

static void print_items(const Item *items, int n) {
    for (int i = 0; i < n; i++) {
        printf("Item %d -> weight: %d, value: %d, ratio: %.2f\n",
               i + 1, items[i].weight, items[i].value, ratio(&items[i]));
    }
}

int main(void) {
    int n;
    int capacity;
    Item *items;

    if (scanf("%d", &n) != 1 || n <= 0) {
        return 1;
    }

    items = (Item *)malloc((size_t)n * sizeof(Item));
    if (items == NULL) {
        return 1;
    }

    for (int i = 0; i < n; i++) {
        if (scanf("%d %d", &items[i].weight, &items[i].value) != 2 || items[i].weight <= 0) {
            free(items);
            return 1;
        }
    }

    if (scanf("%d", &capacity) != 1 || capacity < 0) {
        free(items);
        return 1;
    }

    printf("Raw input items:\n");
    print_items(items, n);
    printf("Capacity: %d\n", capacity);

    printf("Items sorted by ratio:\n");
    sort_by_ratio_desc(items, n);
    print_items(items, n);

    printf("Expected output (maximum value): %.2f\n", fractional_knapsack(items, n, capacity));

    free(items);
    return 0;
}
