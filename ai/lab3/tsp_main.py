import cProfile
from random import seed

from genetic_algorithm import GeneticAlgorithm
from graph_parameters import GraphParameters
from parameters import FitnessType, GenerationType, SelectionType
from tsp_chromosome import TspChromosome
from tsp_graph import TspGraph

graph = TspGraph.from_path("tsp_data/hard_02_52.txt", separator=",")
params = GraphParameters(graph,
                         TspChromosome,
                         1000,
                         graph.no_nodes,
                         graph.nodes,
                         FitnessType.SMALLER_BETTER,
                         generation_type=GenerationType.SIMPLE,
                         selection_type=SelectionType.BINARY_TOURNAMENT,
                         elitist_percentage=0.15,
                         no_crossover_points=10,
                         mutation_chance=0.03)


