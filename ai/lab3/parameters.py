from enum import Enum


class FitnessType(Enum):
    SMALLER_BETTER = 1
    BIGGER_BETTER = 2


class GenerationType(Enum):
    SIMPLE = 1
    STEADY = 3


class SelectionType(Enum):
    BINARY_TOURNAMENT = 1


def smaller_better_check(first_fitness, second_fitness):
    return first_fitness < second_fitness


def bigger_better_check(first_fitness, second_fitness):
    return first_fitness > second_fitness


def smaller_better_fitness_adjust(fitness):
    return -fitness


def bigger_better_fitness_adjust(fitness):
    return fitness


class Parameters:
    def __init__(self, chromosome_type, population_size, no_genes, gene_values, fitness_type, **kwargs):
        self.chromosome_type = chromosome_type
        self.population_size = population_size
        self.no_genes = no_genes
        self.gene_values = gene_values
        self.fitness_type = fitness_type

        self.generation_type = kwargs.get("generation_type", GenerationType.SIMPLE)
        self.selection_type = kwargs.get("selection_type", SelectionType.BINARY_TOURNAMENT)
        self.elitist_percentage = kwargs.get("elitist_percentage", 0.1)
        self.elitist_population_size = int(population_size * self.elitist_percentage) // 2 * 2
        self.no_crossover_points = kwargs.get("no_crossover_points", 1)
        self.mutation_chance = kwargs.get("mutation_chance", 0)
        self.debug = False

        if self.fitness_type == FitnessType.SMALLER_BETTER:
            self.is_fitness_better_than = smaller_better_check
            self.fitness_adjust = smaller_better_fitness_adjust
        elif self.fitness_type == FitnessType.BIGGER_BETTER:
            self.is_fitness_better_than = bigger_better_check
            self.fitness_adjust = bigger_better_fitness_adjust
        else:
            raise ValueError("Invalid fitness type")

        if self.population_size % 2 != 0:
            raise ValueError("Population size cannot be uneven")

        if self.no_crossover_points % 2 != 0:
            raise ValueError("Number of crossover points cannot be uneven")
