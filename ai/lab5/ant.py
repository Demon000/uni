class Ant:
    def __init__(self, parameters):
        self.parameters = parameters
        self.tour_edges = None
        self.tour_weight = None

    def build_tour(self):
        self.tour_edges = []
        self.tour_weight = 0

        available_nodes = self.parameters.graph.get_available_nodes()
        starting_node = self.parameters.graph.extract_random_node(available_nodes)
        current_node = starting_node
        cycled_back = False

        while True:
            if len(available_nodes):
                edge = self.parameters.graph.extract_best_edge(current_node, available_nodes)
            elif not cycled_back:
                edge = self.parameters.graph.edges_matrix[current_node.index][starting_node.index]
                cycled_back = True
            else:
                break

            self.tour_edges.append(edge)
            self.tour_weight += edge.weight
            current_node = edge.to_node

    def leave_pheromones(self):
        for edge in self.tour_edges:
            quantity = self.parameters.pheromones_leave_quantity / self.tour_weight
            edge.add_pheromones(quantity)

    def get_tour_node_indices(self):
        tour_indices = []
        for edge in self.tour_edges:
            tour_indices.append(edge.from_node.index)

        final_i = 0
        for i in range(len(tour_indices)):
            index = tour_indices[i]
            if index == 0:
                final_i = i
                break

        return tour_indices[final_i:] + list(reversed(tour_indices[:final_i]))

    def __str__(self):
        tour_node_indices = self.get_tour_node_indices()
        return f"Ant -> weight: {self.tour_weight}, " \
               f"no_nodes: {len(tour_node_indices)}, " \
               f"nodes: {tour_node_indices}"
