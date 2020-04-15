from operator import attrgetter
from random import random, choices, choice

import matplotlib.pyplot as plt

from ant import Ant
from parameters import GraphType


class ACO:
    def __init__(self, parameters):
        self.parameters = parameters
        self.colony = None
        self.iteration = 0

    def create_colony(self):
        self.colony = [Ant(self.parameters) for _ in range(self.parameters.no_ants)]

    def tour_colony(self):
        for ant in self.colony:
            ant.build_tour()

    def rank_colony(self):
        self.colony.sort(key=attrgetter("tour_weight"))

    def get_best_ant(self):
        return self.colony[0]

    def get_average_tour_weight(self):
        total_tour_weight = 0
        for ant in self.colony:
            total_tour_weight += ant.tour_weight
        return total_tour_weight / self.parameters.no_ants

    def evaporate_pheromones(self):
        self.parameters.graph.evaporate_pheromones()

    def leave_pheromones(self):
        colony_elite = self.colony[:self.parameters.no_elite_ants]
        for ant in colony_elite:
            ant.leave_pheromones()

    def change_graph(self):
        if self.parameters.graph_type != GraphType.DYNAMIC:
            return

        if random() < self.parameters.graph_reset_chance:
            print("Resetting graph")
            self.parameters.graph.reset()

        if random() < self.parameters.graph_highway_chance:
            print(f"Halving the weight of {self.parameters.graph_highway_length} edges")
            highway_edges = choices(self.parameters.graph.edges, k=self.parameters.graph_highway_length)
            for edge in highway_edges:
                edge.factor = 0.5

        if random() < self.parameters.graph_roadblock_chance:
            print(f"Doubling the weight of {self.parameters.graph_highway_length} edges")
            roadblock_edges = choices(self.parameters.graph.edges, k=self.parameters.graph_roadblock_length)
            for edge in roadblock_edges:
                edge.factor = 2

        if random() < self.parameters.graph_quarantine_chance:
            print("Disabling a node")
            node = choice(self.parameters.graph.nodes)
            node.disabled = True

    def run_iterations(self, no_iterations, console=False, plot=False):
        best_tour_weights = []
        average_tour_weights = []

        for _ in range(no_iterations):
            self.create_colony()
            self.tour_colony()
            self.rank_colony()
            self.evaporate_pheromones()
            self.leave_pheromones()
            self.change_graph()

            best_ant = self.get_best_ant()
            average_tour_weight = self.get_average_tour_weight()
            best_tour_weights.append(best_ant.tour_weight)
            average_tour_weights.append(average_tour_weight)

            self.iteration += 1

            if console:
                print(self)

        if plot:
            plt.plot(best_tour_weights, c="red")
            plt.plot(average_tour_weights, c="blue")
            plt.show()

    def __str__(self):
        return f"Iteration: {self.iteration}\n" \
               f"Best ant: {self.get_best_ant()}\n" \
               f"Average tour weight: {self.get_average_tour_weight()}\n\n"
