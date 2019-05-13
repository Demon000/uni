#include <stdio.h>
#include <stdlib.h>

#define INFINITY 1 << 28
#define NO_PARENT -1

typedef struct Node {
    int distance;
    int parent;
} Node;

Node* Node__create() {
    Node* node = malloc(sizeof(Node));

    node->distance = INFINITY;
    node->parent = NO_PARENT;

    return node;
}

void Node__destroy(Node* node) {
    free(node);
}

typedef struct Edge {
    int first;
    int second;
    int weight;
} Edge;

Edge* Edge__create(int first, int second, int weight) {
    Edge* edge = malloc(sizeof(Edge));

    edge->first = first;
    edge->second = second;
    edge->weight = weight;

    return edge;
}

void Edge__destroy(Edge* edge) {
    free(edge);
}

int main(int argc, char** argv) {
    int no_nodes;
    int no_edges;

    if (argc < 2) {
        printf("./bellman_ford <file_name>\n");
        return 0;
    }

    FILE* file = fopen(argv[1], "r");

    fscanf(file, "%d %d", &no_nodes, &no_edges);

    Node** nodes = malloc(sizeof(Node*) * no_nodes);
    Edge** edges = malloc(sizeof(Edge*) * no_edges);

    for (int i = 0; i < no_nodes; i++) {
        nodes[i] = Node__create();
    }
    nodes[0]->distance = 0;

    for (int i = 0; i < no_edges; i++) {
        int first, second, weight;
        fscanf(file, "%d %d %d", &first, &second, &weight);

        edges[i] = Edge__create(first, second, weight);
    }

    fclose(file);

    for (int i = 0; i < no_nodes - 1; i++) {
        for (int e = 0; e < no_edges; e++) {
            Edge* edge = edges[e];
            int first = edge->first;
            int second = edge->second;

            if (nodes[first]->distance + edge->weight < nodes[second]->distance) {
                nodes[second]->distance = nodes[first]->distance + edge->weight;
                nodes[second]->parent = first;
            }
        }
    }

    for (int e = 0; e < no_edges; e++) {
        Edge* edge = edges[e];
        int first = edge->first;
        int second = edge->second;

        if (nodes[first]->distance + edge->weight < nodes[second]->distance) {
            printf("Negative cycle.");
            return 0;
        }
    }

    for (int i = 1; i < no_nodes; i++) {
        Node* node = nodes[i];
        printf("%d ", node->distance);
    }
    printf("\n");

    for (int i = 0; i < no_nodes; i++) {
        Node__destroy(nodes[i]);
    }
    free(nodes);

    for (int i = 0; i < no_edges; i++) {
        Edge__destroy(edges[i]);
    }
    free(edges);

    return 0;
}
