#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Edge {
    int from;
    int to;
};

struct Edges {
    struct Edge *items;
    int last_edge_index;
    int number_of_edges;
    int number_of_points;
};

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

void read_list(FILE *file, struct Edges *edges) {
    int number_of_edges;
    fscanf(file, "%d", &number_of_edges);

    Edges__init(edges, number_of_edges);

    while (number_of_edges) {
        int from;
        int to;
        fscanf(file, "%d %d", &from, &to);
        Edges__add(edges, from, to);
        number_of_edges--;
    }
}

void write_adjacent(FILE *file, struct Edges *edges) {
    int adjacent[edges->number_of_edges][edges->number_of_edges];
    memset(&adjacent, 0,
            sizeof(int) * edges->number_of_points * edges->number_of_points);

    for (int edge_index = 0; edge_index < edges->number_of_edges; edge_index++) {
        int from = Edges__get_from(edges, edge_index);
        int to = Edges__get_to(edges, edge_index);

        adjacent[from - 1][to - 1] = 1;
        adjacent[to - 1][from - 1] = 1;
    }

    fprintf(file, "%d\n", edges->number_of_points);
    for (int point_one = 0; point_one < edges->number_of_points; point_one++) {
        for (int point_two = 0; point_two < edges->number_of_points; point_two++) {
            fprintf(file, "%d ", adjacent[point_one][point_two]);
        }
        fprintf(file, "\n");
    }
}

int read_adjacent(FILE *file, struct Edges *edges) {
    int max_point;
    fscanf(file, "%d", &max_point);

    int adjacent[max_point][max_point];
    memset(&adjacent, 0, sizeof(int) * max_point * max_point);

    int number_of_edges = 0;
    for (int point_one = 0; point_one < max_point; point_one++) {
        for (int point_two = 0; point_two < max_point; point_two++) {
            fscanf(file, "%d", &adjacent[point_one][point_two]);
            if (adjacent[point_one][point_two] == 1 && point_two >= point_one) {
                number_of_edges++;
            }
        }
    }

    Edges__init(edges, number_of_edges);

    for (int point_one = 0; point_one < max_point; point_one++) {
        for (int point_two = point_one; point_two < max_point; point_two++) {
            if (adjacent[point_one][point_two] == 1) {
                Edges__add(edges, point_one + 1, point_two + 1);
            }
        }
    }

    return number_of_edges;
}

void write_incidence(FILE *file, struct Edges *edges) {
    fprintf(file, "%d %d\n", edges->number_of_points, edges->number_of_edges);

    for (int point = 1; point <= edges->number_of_points; point++) {
        for (int edge_index = 0; edge_index < edges->number_of_edges; edge_index++) {
            if (Edges__is_point(edges, edge_index, point)) {
                fprintf(file, "1 ");
            } else {
                fprintf(file, "0 ");
            }
        }

        fprintf(file, "\n");
    }
}

int read_incidence(FILE *file, struct Edges *edges) {
    int max_point, number_of_edges, value;
    fscanf(file, "%d %d", &max_point, &number_of_edges);

    Edges__init(edges, number_of_edges);

    for (int point = 1; point <= max_point; point++) {
        for (int edge_index = 0; edge_index < number_of_edges; edge_index++) {
            fscanf(file, "%d", &value);
            if (value == 1) {
                Edges__set_available(edges, edge_index, point);
            }
        }
    }

    return number_of_edges;
}

void write_list(FILE *file, struct Edges *edges) {
    fprintf(file, "%d\n", edges->number_of_edges);

    for (int edge_index = 0; edge_index < edges->number_of_edges; edge_index++) {
        fprintf(file, "%d %d\n", Edges__get_from(edges, edge_index),
                Edges__get_to(edges, edge_index));
    }
}

void print_edges(struct Edges *edges, char *message) {
    printf("%s\n", message);
    for (int edge_index = 0; edge_index < edges->number_of_edges; edge_index++) {
        printf("%d %d\n", Edges__get_from(edges, edge_index),
                Edges__get_to(edges, edge_index));
    }
    printf("\n");
}


int main() {
    struct Edges edges;
    FILE* file;

    file = fopen("list_input.txt", "r");
    read_list(file, &edges);
    fclose(file);
    print_edges(&edges, "edges read using list:");

    file = fopen("adjacent.txt", "w");
    write_adjacent(file, &edges);
    fclose(file);

    Edges__deinit(&edges);

    file = fopen("adjacent.txt", "r");
    read_adjacent(file, &edges);
    fclose(file);
    print_edges(&edges, "edges read using adjacent:");

    file = fopen("incidence.txt", "w");
    write_incidence(file, &edges);
    fclose(file);

    Edges__deinit(&edges);

    file = fopen("incidence.txt", "r");
    read_incidence(file, &edges);
    fclose(file);
    print_edges(&edges, "edges read using incidence:");

    file = fopen("list_output.txt", "w");
    write_list(file, &edges);
    fclose(file);

    Edges__deinit(&edges);
}
