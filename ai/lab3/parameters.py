from enum import Enum
from functools import partial


class GenerationType(Enum):
    SIMPLE = 1
    ELITISM = 2
    STEADY = 3


class CrossoverType(Enum):
    TRANSFER = 1


class MutationType(Enum):
    SWAP = 1


class Parameters:
    def __init__(self, chromosome_type, population_size, fitness_fn, no_genes, gene_values, **kwargs):
        self.chromosome_type = chromosome_type
        self.population_size = population_size
        self.fitness_fn = partial(fitness_fn, self)
        self.no_genes = no_genes
        self.gene_values = gene_values

        self.generation_type = kwargs.get("generation_type", GenerationType.SIMPLE)
        self.crossover_type = kwargs.get("crossover_type", CrossoverType.TRANSFER)
        self.mutation_type = kwargs.get("mutation_type", MutationType.SWAP)
        self.mutation_chance = kwargs.get("mutation_chance", 0)
