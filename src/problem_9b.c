#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int src;
    int dest;
    int weight;
} Edge;

static void print_edges(const Edge *edges, int E) {
    for (int i = 0; i < E; i++) {
        printf("%d -> %d %d\n", edges[i].src, edges[i].dest, edges[i].weight);
    }
}

static void print_distances(const int *dist, int V) {
    printf("Vertex Distance from Source\n");
    for (int i = 0; i < V; i++) {
        if (dist[i] >= INT_MAX / 4) {
            printf("%d INF\n", i);
        } else {
            printf("%d %d\n", i, dist[i]);
        }
    }
}

void bellman_ford(int V, int E, Edge *edges, int src) {
    int *dist = (int *)malloc((size_t)V * sizeof(int));
    int inf = INT_MAX / 2;

    if (dist == NULL) {
        exit(1);
    }

    for (int i = 0; i < V; i++) {
        dist[i] = inf;
    }
    dist[src] = 0;

    for (int i = 1; i <= V - 1; i++) {
        int updated = 0;

        for (int j = 0; j < E; j++) {
            if (dist[edges[j].src] < inf &&
                dist[edges[j].src] + edges[j].weight < dist[edges[j].dest]) {
                dist[edges[j].dest] = dist[edges[j].src] + edges[j].weight;
                updated = 1;
            }
        }

        if (!updated) {
            break;
        }
    }

    for (int j = 0; j < E; j++) {
        if (dist[edges[j].src] < inf &&
            dist[edges[j].src] + edges[j].weight < dist[edges[j].dest]) {
            printf("Graph contains a negative-weight cycle\n");
            free(dist);
            return;
        }
    }

    print_distances(dist, V);
    free(dist);
}

int main(void) {
    int V;
    int E;
    int src;

    if (scanf("%d %d", &V, &E) != 2 || V <= 0 || E < 0) {
        return 1;
    }

    Edge *edges = (Edge *)malloc((size_t)E * sizeof(Edge));
    if (edges == NULL) {
        return 1;
    }

    for (int i = 0; i < E; i++) {
        if (scanf("%d %d %d", &edges[i].src, &edges[i].dest, &edges[i].weight) != 3 ||
            edges[i].src < 0 || edges[i].src >= V ||
            edges[i].dest < 0 || edges[i].dest >= V) {
            free(edges);
            return 1;
        }
    }

    if (scanf("%d", &src) != 1 || src < 0 || src >= V) {
        free(edges);
        return 1;
    }

    printf("Raw input edge list:\n");
    print_edges(edges, E);
    printf("Source vertex: %d\n", src);
    printf("Expected output (shortest distances or cycle detection):\n");
    bellman_ford(V, E, edges, src);

    free(edges);
    return 0;
}
