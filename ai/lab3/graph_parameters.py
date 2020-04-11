from parameters import Parameters


class GraphParameters(Parameters):
    def __init__(self, graph, *args, **kwargs):
        super().__init__(*args, **kwargs)

        self.graph = graph
