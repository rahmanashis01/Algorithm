#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int src;
    int dest;
    int weight;
} Edge;

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

static void print_mst(const Edge *mst, int mst_size, int total_weight) {
    printf("Edge Weight\n");
    for (int i = 0; i < mst_size; i++) {
        printf("%d - %d %d\n", mst[i].src, mst[i].dest, mst[i].weight);
    }
    printf("Total weight: %d\n", total_weight);
}

static int compare_edges(const void *a, const void *b) {
    const Edge *left = (const Edge *)a;
    const Edge *right = (const Edge *)b;
    return left->weight - right->weight;
}

static int find_set(int *parent, int node) {
    if (parent[node] != node) {
        parent[node] = find_set(parent, parent[node]);
    }
    return parent[node];
}

static void union_sets(int *parent, int *rank, int u, int v) {
    int root_u = find_set(parent, u);
    int root_v = find_set(parent, v);

    if (root_u == root_v) {
        return;
    }

    if (rank[root_u] < rank[root_v]) {
        parent[root_u] = root_v;
    } else if (rank[root_u] > rank[root_v]) {
        parent[root_v] = root_u;
    } else {
        parent[root_v] = root_u;
        rank[root_u]++;
    }
}

void prims_mst(int V, int graph[V][V], Edge *mst, int *mst_size, int *total_weight) {
    int *parent = (int *)malloc((size_t)V * sizeof(int));
    int *key = (int *)malloc((size_t)V * sizeof(int));
    int *visited = (int *)malloc((size_t)V * sizeof(int));

    if (parent == NULL || key == NULL || visited == NULL) {
        free(parent);
        free(key);
        free(visited);
        exit(1);
    }

    for (int i = 0; i < V; i++) {
        key[i] = INT_MAX;
        visited[i] = 0;
        parent[i] = -1;
    }

    key[0] = 0;

    for (int count = 0; count < V - 1; count++) {
        int min_key = INT_MAX;
        int u = -1;

        for (int v = 0; v < V; v++) {
            if (!visited[v] && key[v] < min_key) {
                min_key = key[v];
                u = v;
            }
        }

        if (u == -1) {
            break;
        }

        visited[u] = 1;

        for (int v = 0; v < V; v++) {
            if (graph[u][v] > 0 && !visited[v] && graph[u][v] < key[v]) {
                key[v] = graph[u][v];
                parent[v] = u;
            }
        }
    }

    *mst_size = 0;
    *total_weight = 0;

    for (int v = 1; v < V; v++) {
        if (parent[v] != -1) {
            mst[*mst_size].src = parent[v];
            mst[*mst_size].dest = v;
            mst[*mst_size].weight = graph[parent[v]][v];
            *total_weight += graph[parent[v]][v];
            (*mst_size)++;
        }
    }

    free(parent);
    free(key);
    free(visited);
}

void kruskals_mst(Edge *edges, int E, int V, Edge *mst, int *mst_size, int *total_weight) {
    int *parent = (int *)malloc((size_t)V * sizeof(int));
    int *rank = (int *)calloc((size_t)V, sizeof(int));

    if (parent == NULL || rank == NULL) {
        free(parent);
        free(rank);
        exit(1);
    }

    for (int i = 0; i < V; i++) {
        parent[i] = i;
    }

    qsort(edges, (size_t)E, sizeof(Edge), compare_edges);

    *mst_size = 0;
    *total_weight = 0;

    for (int i = 0; i < E && *mst_size < V - 1; i++) {
        int root_u = find_set(parent, edges[i].src);
        int root_v = find_set(parent, edges[i].dest);

        if (root_u != root_v) {
            mst[*mst_size] = edges[i];
            *total_weight += edges[i].weight;
            (*mst_size)++;
            union_sets(parent, rank, root_u, root_v);
        }
    }

    free(parent);
    free(rank);
}

int main(void) {
    int V;

    if (scanf("%d", &V) != 1 || V <= 0) {
        return 1;
    }

    int (*graph)[V] = malloc((size_t)V * sizeof(*graph));
    Edge *edges = (Edge *)malloc((size_t)V * (size_t)V * sizeof(Edge));
    Edge *prim_mst = (Edge *)malloc((size_t)(V - 1) * sizeof(Edge));
    Edge *kruskal_mst = (Edge *)malloc((size_t)(V - 1) * sizeof(Edge));
    int edge_count = 0;
    int prim_size;
    int kruskal_size;
    int prim_total;
    int kruskal_total;

    if (graph == NULL || edges == NULL || prim_mst == NULL || kruskal_mst == NULL) {
        free(graph);
        free(edges);
        free(prim_mst);
        free(kruskal_mst);
        return 1;
    }

    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (scanf("%d", &graph[i][j]) != 1 || graph[i][j] < 0) {
                free(graph);
                free(edges);
                free(prim_mst);
                free(kruskal_mst);
                return 1;
            }

            if (j > i && graph[i][j] > 0) {
                edges[edge_count].src = i;
                edges[edge_count].dest = j;
                edges[edge_count].weight = graph[i][j];
                edge_count++;
            }
        }
    }

    printf("Raw input adjacency matrix:\n");
    print_matrix(V, graph);

    prims_mst(V, graph, prim_mst, &prim_size, &prim_total);
    kruskals_mst(edges, edge_count, V, kruskal_mst, &kruskal_size, &kruskal_total);

    printf("Expected output (Prim's MST):\n");
    print_mst(prim_mst, prim_size, prim_total);

    printf("Expected output (Kruskal's MST):\n");
    print_mst(kruskal_mst, kruskal_size, kruskal_total);

    printf("MST weights match: %s\n", prim_total == kruskal_total ? "Yes" : "No");

    free(graph);
    free(edges);
    free(prim_mst);
    free(kruskal_mst);
    return 0;
}
