import cProfile
from random import seed

from aco import ACO
from graph import Graph
from parameters import Parameters, GraphType

parameters = Parameters(graph_type=GraphType.DYNAMIC,
                        graph_reset_chance=0.01,
                        graph_highway_chance=0.05,
                        graph_highway_length=3,
                        graph_roadblock_chance=0.05,
                        graph_roadblock_length=3,
                        graph_quarantine_chance=0.01,
                        no_ants=30,
                        elite_ants_percentage=0.1,
                        pheromones_importance=1,
                        pheromones_leave_quantity=1,
                        pheromones_evaporation_rate=0.02,
                        weight_importance=3)
parameters.graph = Graph.from_path("data/berlin52.txt", parameters, separator=",")

seed(103)

profiled = False
console = True
plot = True
no_generations = 500
aco = ACO(parameters)


def run():
    aco.run_iterations(no_generations, console=console, plot=plot)


if profiled:
    cProfile.run(run.__code__)
else:
    run()
