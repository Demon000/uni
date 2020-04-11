import networkx as nx


class CommunitiesGraph:
    def __init__(self, data):
        self.data = data
        self.start_index = min(list(self.data.nodes))
        self.nodes = [x - self.start_index for x in list(self.data.nodes)]
        self.no_nodes = data.number_of_nodes()
        self.no_edges = data.number_of_edges()
        self.adjacency = None
        self.degrees = None

        self.build_adjacency()
        self.build_degrees()

    def build_adjacency(self):
        self.adjacency = []

        for first_index in self.data:
            self.adjacency.append([])
            for second_index in self.data:
                is_adjacent = self.data.has_edge(first_index, second_index)
                self.adjacency[-1].append(is_adjacent)

    def build_degrees(self):
        self.degrees = []

        for index in self.data:
            self.degrees.append(self.data.degree(index))

    @staticmethod
    def from_path(file_path):
        data = nx.read_gml(file_path, label='id')
        return CommunitiesGraph(data)
