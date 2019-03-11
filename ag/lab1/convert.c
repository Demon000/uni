#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "edges.h"

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

void write_adjacence(FILE *file, struct Edges *edges) {
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

int read_adjacence(FILE *file, struct Edges *edges) {
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

    // list -> adjacence
    file = fopen("list_input.txt", "r");
    read_list(file, &edges);
    fclose(file);
    print_edges(&edges, "edges read using list:");

    file = fopen("adjacence.txt", "w");
    write_adjacence(file, &edges);
    fclose(file);

    Edges__deinit(&edges);

    // adjacence -> incidence
    file = fopen("adjacence.txt", "r");
    read_adjacence(file, &edges);
    fclose(file);
    print_edges(&edges, "edges read using adjacence:");

    file = fopen("incidence.txt", "w");
    write_incidence(file, &edges);
    fclose(file);

    Edges__deinit(&edges);

    // incidence -> adjacence
    file = fopen("incidence.txt", "r");
    read_incidence(file, &edges);
    fclose(file);
    print_edges(&edges, "edges read using incidence:");

    file = fopen("adjacence.txt", "w");
    write_adjacence(file, &edges);
    fclose(file);

    Edges__deinit(&edges);

    // adjacence -> list
    file = fopen("adjacence.txt", "r");
    read_adjacence(file, &edges);
    fclose(file);
    print_edges(&edges, "edges read using adjacence:");

    file = fopen("list_output.txt", "w");
    write_list(file, &edges);
    fclose(file);

    Edges__deinit(&edges);
}
