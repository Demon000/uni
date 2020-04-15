from random import choice, choices


class Node:
    def __init__(self, index, parameters):
        self.index = index
        self.disabled = False
        self.parameters = parameters


class Edge:
    INVALID_SCORE = -1

    def __init__(self, from_node, to_node, weight, parameters):
        self.__weight = weight
        self.__factor = 1
        self.__pre = None

        self.__pheromones = 0
        self.__post = None
        self.__score = None

        self.from_node = from_node
        self.to_node = to_node
        self.parameters = parameters

    @property
    def score(self):
        if self.weight == 0:
            return Edge.INVALID_SCORE

        if self.__score is None:
            if self.__pre is None:
                self.__pre = 1 / self.weight
                if self.parameters.weight_importance != 1:
                    self.__pre **= self.parameters.weight_importance

            if self.__post is None:
                self.__post = self.__pheromones
                if self.parameters.pheromones_importance != 1:
                    self.__post **= self.parameters.pheromones_importance

            self.__score = self.__pre * self.__post

        return self.__score

    @property
    def weight(self):
        return self.__weight * self.__factor

    @property
    def factor(self):
        return self.__factor

    @factor.setter
    def factor(self, value):
        self.__factor = value
        self.__pre = None
        self.__score = None

    def add_pheromones(self, value):
        self.__pheromones += value
        self.__post = None
        self.__score = None

    def evaporate_pheromones(self):
        self.__pheromones *= (1 - self.parameters.pheromones_evaporation_rate)
        self.__post = None
        self.__score = None


class Graph:
    def __init__(self, nodes_indices, weights_matrix, parameters):
        self.parameters = parameters

        self.nodes = []
        for node_index in nodes_indices:
            node = Node(node_index, parameters)
            self.nodes.append(node)

        self.edges_matrix = []
        self.edges = []
        for from_node in self.nodes:
            self.edges_matrix.append([])
            for to_node in self.nodes:
                weight = weights_matrix[from_node.index][to_node.index]
                edge = Edge(from_node, to_node, weight, parameters)
                self.edges.append(edge)
                self.edges_matrix[-1].append(edge)

    def reset(self):
        for node in self.nodes:
            node.disabled = False

        for edge in self.edges:
            edge.factor = 1

    def evaporate_pheromones(self):
        for edge in self.edges:
            edge.evaporate_pheromones()

    def get_available_nodes(self):
        available_nodes = []
        for node in self.nodes:
            if not node.disabled:
                available_nodes.append(node)
        return available_nodes

    def get_edge_between(self, node, next_node):
        return self.edges_matrix[node.index][next_node.index]

    def extract_best_edge(self, current_node, available_nodes):
        if len(available_nodes) == 1:
            last_node = available_nodes.pop()
            return self.edges_matrix[current_node.index][last_node.index]

        edges = []
        cumulative_scores = []
        for node in available_nodes:
            edge = self.edges_matrix[current_node.index][node.index]
            score = edge.score
            if score == Edge.INVALID_SCORE:
                continue

            if len(cumulative_scores):
                score += cumulative_scores[-1]

            cumulative_scores.append(score)
            edges.append(edge)

        edge = choices(edges, cum_weights=cumulative_scores)[0]
        available_nodes.remove(edge.to_node)
        return edge

    def extract_random_node(self, available_nodes):
        node = None

        while node is None or node.disabled:
            node = choice(available_nodes)

        available_nodes.remove(node)

        return node

    @staticmethod
    def from_path(file_path, parameters, separator=" "):
        with open(file_path, "r") as file:
            first_line = file.readline()
            rest_of_lines = file.readlines()

            no_nodes = int(first_line)
            nodes_indices = range(no_nodes)

            weights_matrix = []
            for line in rest_of_lines:
                weights = [int(s) for s in line.split(separator)]
                weights_matrix.append(weights)

            return Graph(nodes_indices, weights_matrix, parameters)
