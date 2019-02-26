#include <stdlib.h>
#include <string.h>

#include "edges.h"

void Edge__init(struct Edge *edge) {
    edge->from = -1;
    edge->to = -1;
}

void Edge__set(struct Edge *edge, int from, int to) {
    edge->from = from;
    edge->to = to;
}

void Edges__init(struct Edges *edges, int number_of_edges) {
    edges->items = malloc(sizeof(struct Edge) * number_of_edges);
    edges->last_edge_index = -1;
    edges->number_of_edges = number_of_edges;
    edges->number_of_points = 0;

    for (int edge_index = 0; edge_index < number_of_edges; edge_index++) {
        Edge__init(&edges->items[edge_index]);
    }
}

void Edges__deinit(struct Edges *edges) {
    free(edges->items);
}

void Edges__set(struct Edges *edges, int edge_index, int from, int to) {
    if (from > edges->number_of_points) {
        edges->number_of_points = from;
    }

    if (to > edges->number_of_points) {
        edges->number_of_points = to;
    }

    Edge__set(&edges->items[edge_index], from, to);
}

void Edges__add(struct Edges *edges, int from, int to) {
    int edge_index = ++edges->last_edge_index;

    Edges__set(edges, edge_index, from, to);
}

struct Edge* Edges__get(struct Edges *edges, int edge_index) {
    return &edges->items[edge_index];
}

int Edges__get_from(struct Edges *edges, int edge_index) {
    return Edges__get(edges, edge_index)->from;
}

int Edges__get_to(struct Edges *edges, int edge_index) {
    return Edges__get(edges, edge_index)->to;
}

void Edges__set_available(struct Edges *edges, int edge_index, int point) {
    int from = Edges__get_from(edges, edge_index);
    int to = Edges__get_to(edges, edge_index);

    if (from == -1) {
        Edges__set(edges, edge_index, point, to);
    } else if (to == -1) {
        Edges__set(edges, edge_index, from, point);
    }
}

int Edges__is_point(struct Edges *edges, int edge, int point) {
    return Edges__get_from(edges, edge) == point ||
            Edges__get_to(edges, edge) == point;
}
