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

void Edge__init(struct Edge *edge);
void Edge__set(struct Edge *edge, int from, int to);

void Edges__init(struct Edges *edges, int number_of_edges);
void Edges__deinit(struct Edges *edges);
void Edges__set(struct Edges *edges, int edge_index, int from, int to);
void Edges__add(struct Edges *edges, int from, int to);
struct Edge* Edges__get(struct Edges *edges, int edge_index);
int Edges__get_from(struct Edges *edges, int edge_index);
int Edges__get_to(struct Edges *edges, int edge_index);
void Edges__set_available(struct Edges *edges, int edge_index, int point);
int Edges__is_point(struct Edges *edges, int edge, int point);
