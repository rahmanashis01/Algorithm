#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static void print_matrix(int V, int graph[V][V]) {
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            printf("%d", graph[i][j]);
            if (j < V - 1) {
                printf(" ");
            }
        }
        printf("\n");
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

void dijkstra(int V, int graph[V][V], int src) {
    int *dist = (int *)malloc((size_t)V * sizeof(int));
    int *visited = (int *)calloc((size_t)V, sizeof(int));

    if (dist == NULL || visited == NULL) {
        free(dist);
        free(visited);
        exit(1);
    }

    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX / 2;
    }
    dist[src] = 0;

    for (int count = 0; count < V; count++) {
        int min_dist = INT_MAX / 2;
        int u = -1;

        for (int v = 0; v < V; v++) {
            if (!visited[v] && dist[v] < min_dist) {
                min_dist = dist[v];
                u = v;
            }
        }

        if (u == -1) {
            break;
        }

        visited[u] = 1;

        for (int v = 0; v < V; v++) {
            if (graph[u][v] > 0 && !visited[v] && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    print_distances(dist, V);

    free(dist);
    free(visited);
}

int main(void) {
    int V;
    int src;

    if (scanf("%d", &V) != 1 || V <= 0) {
        return 1;
    }

    int (*graph)[V] = malloc((size_t)V * sizeof(*graph));
    if (graph == NULL) {
        return 1;
    }

    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (scanf("%d", &graph[i][j]) != 1 || graph[i][j] < 0) {
                free(graph);
                return 1;
            }
        }
    }

    if (scanf("%d", &src) != 1 || src < 0 || src >= V) {
        free(graph);
        return 1;
    }

    printf("Raw input adjacency matrix:\n");
    print_matrix(V, graph);
    printf("Source vertex: %d\n", src);
    printf("Expected output (shortest distances):\n");
    dijkstra(V, graph, src);

    free(graph);
    return 0;
}
