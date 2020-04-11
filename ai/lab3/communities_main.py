#!/usr/bin/env python3

import cProfile

from communities_chromosome import CommunitiesChromosome
from graph_parameters import GraphParameters
from genetic_algorithm import GeneticAlgorithm
from communities_graph import CommunitiesGraph
from parameters import GenerationType, CrossoverType, MutationType, FitnessType

graph = CommunitiesGraph.from_path("communities_data/karate.gml")
params = GraphParameters(graph,
                         CommunitiesChromosome,
                         300,
                         graph.no_nodes,
                         graph.nodes,
                         fitness_type=FitnessType.BIGGER_BETTER,
                         generation_type=GenerationType.STEADY,
                         crossover_type=CrossoverType.TRANSFER,
                         mutation_type=MutationType.SWAP,
                         mutation_chance=0.60)

no_generations = 400
ga = GeneticAlgorithm(params)

cProfile.run(f"ga.run_print_generations({no_generations})")
