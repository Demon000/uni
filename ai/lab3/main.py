#!/usr/bin/env python3

import cProfile
import matplotlib.pyplot as plt

from communities_chromosome import CommunitiesChromosome
from communities_parameters import CommunitiesParameters
from genetic_algorithm import GeneticAlgorithm
from graph import Graph
from parameters import GenerationType, CrossoverType, MutationType


def communities_fitness(parameters, chromosome):
    two_m = 2 * graph.no_edges
    q = 0.0

    for first_index in parameters.graph.nodes:
        first_degree = graph.degrees[first_index]
        first_community = chromosome.communities[first_index]
        for second_index in parameters.graph.nodes:
            second_degree = graph.degrees[second_index]
            second_community = chromosome.communities[second_index]

            adjacency = 1 if graph.adjacency[first_index][second_index] else 0

            if first_community == second_community:
                q += adjacency - first_degree * second_degree / two_m

    return q / two_m


graph = Graph.from_path("./data/karate.gml")
params = CommunitiesParameters(graph,
                               CommunitiesChromosome,
                               300,
                               communities_fitness,
                               graph.no_nodes,
                               graph.nodes,
                               generation_type=GenerationType.STEADY,
                               crossover_type=CrossoverType.TRANSFER,
                               mutation_type=MutationType.SWAP,
                               mutation_chance=0.60)

no_generations = 1000
ga = GeneticAlgorithm(params)
average_fitness = []
best_fitness = []

cProfile.run("ga.run_generations(400)")

# for _ in range(no_generations):
#     best_fitness.append(ga.select_best().fitness)
#     average_fitness.append(ga.get_average_fitness())
#     print(ga)
#     ga.next_generation()
#
# plt.plot(best_fitness, c="red")
# plt.plot(average_fitness, c="blue")
# plt.show()
