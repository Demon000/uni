class TspGraph:
    def __init__(self, nodes, distances):
        self.nodes = nodes
        self.no_nodes = len(nodes)
        self.distances = distances

    @staticmethod
    def from_path(file_path, separator=" "):
        with open(file_path, "r") as file:
            first_line = file.readline()
            rest_of_lines = file.readlines()

            no_nodes = int(first_line)
            nodes = range(no_nodes)

            distances = []
            for line in rest_of_lines:
                distances.append([])
                line_distances = [int(s) for s in line.split(separator)]
                for distance in line_distances:
                    distances[-1].append(distance)

            return TspGraph(nodes, distances)
