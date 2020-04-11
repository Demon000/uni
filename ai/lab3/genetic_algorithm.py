from random import choices, choice
import matplotlib.pyplot as plt

from parameters import GenerationType, SelectionType


class GeneticAlgorithm:
    def __init__(self, parameters):
        self.parameters = parameters
        self.generation = 1
        self.next_generation_fn = None

        if self.parameters.selection_type == SelectionType.BINARY_TOURNAMENT:
            self.select_one_fn = self.select_one_binary_tournament
        else:
            raise ValueError("Invalid selection type")

        self.chromosomes = []
        for _ in range(self.parameters.population_size):
            ch = parameters.chromosome_type.random(parameters)
            self.chromosomes.append(ch)

        self.sort_descending()

    def sort_descending(self):
        self.chromosomes.sort(key=lambda c: self.parameters.fitness_adjust(c.fitness), reverse=True)

    def select_one_binary_tournament(self):
        candidates = choices(self.chromosomes, k=2)

        if self.parameters.is_fitness_better_than(candidates[0].fitness, candidates[1].fitness):
            return candidates[0]
        else:
            return candidates[1]

    def select_one(self):
        return self.select_one_fn()

    def produce_offsprings(self):
        first = self.select_one()
        second = self.select_one()
        offsprings = self.parameters.chromosome_type.offsprings(first, second)
        return offsprings

    def produce_offspring(self):
        offsprings = self.produce_offsprings()
        return offsprings[0]

    def create_new_generation(self, n):
        new_chromosomes = []
        length = 0
        while length < n:
            offsprings = self.produce_offsprings()
            new_chromosomes.extend(offsprings)
            length += len(offsprings)

        excess_length = length - n
        while excess_length > 0:
            new_chromosomes.pop()
            excess_length -= 1

        return new_chromosomes

    def next_generation_simple(self, source_population, population_size):
        return self.create_new_generation(population_size)

    def next_generation_steady(self, source_population, population_size):
        new_chromosomes = source_population[:population_size]

        for _ in range(population_size):
            offspring = self.produce_offspring()
            if self.parameters.is_fitness_better_than(offspring.fitness, new_chromosomes[-1].fitness):
                new_chromosomes[-1] = offspring

        return new_chromosomes

    def next_generation(self):
        elite_chromosomes = self.chromosomes[:self.parameters.elitist_population_size]
        pleb_chromosomes = self.chromosomes[self.parameters.elitist_population_size:]

        if self.parameters.generation_type == GenerationType.SIMPLE:
            self.next_generation_fn = self.next_generation_simple
        elif self.parameters.generation_type == GenerationType.STEADY:
            self.next_generation_fn = self.next_generation_steady
        else:
            raise ValueError("Invalid generation type")

        new_population_size = self.parameters.population_size - self.parameters.elitist_population_size
        new_chromosomes = self.next_generation_fn(pleb_chromosomes, new_population_size)
        self.chromosomes = elite_chromosomes + new_chromosomes

        self.sort_descending()
        self.generation += 1

    def get_average_fitness(self):
        total = 0

        for ch in self.chromosomes:
            total += ch.fitness

        return total / self.parameters.population_size

    def run_generations(self, no_generations, console=False, plot=False):
        average_fitness = []
        best_fitness = []

        for _ in range(no_generations):
            if console:
                print(self)

            best_fitness.append(self.chromosomes[0].fitness)
            average_fitness.append(self.get_average_fitness())

            self.next_generation()

        if plot:
            plt.plot(best_fitness, c="red")
            plt.plot(average_fitness, c="blue")
            plt.show()

    def __str__(self):
        return f"Generation: {self.generation}\n" + \
                f"Population size: {self.parameters.population_size}\n" + \
                f"Best chromosome: {self.chromosomes[0]}\n" + \
                f"Average fitness: {self.get_average_fitness()}\n\n"
