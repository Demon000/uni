import operator
from random import choice

from parameters import GenerationType


class GeneticAlgorithm:
    def __init__(self, parameters):
        self.parameters = parameters
        self.chromosomes = []
        self.generation = 0

        for _ in range(self.parameters.population_size):
            ch = parameters.chromosome_type.random(parameters)
            self.chromosomes.append(ch)

    def select_one(self):
        first = choice(self.chromosomes)
        second = choice(self.chromosomes)

        if first.fitness > second.fitness:
            return first
        else:
            return second

    def select_one_offspring(self):
        first = self.select_one()
        second = self.select_one()
        offspring = self.parameters.chromosome_type.offspring(first, second)
        return offspring

    def fill_next_generation(self, new_chromosomes):
        initial_length = len(new_chromosomes)
        while initial_length < self.parameters.population_size:
            offspring = self.select_one_offspring()
            new_chromosomes.append(offspring)
            initial_length += 1

    def next_generation_simple(self):
        new_chromosomes = []
        self.fill_next_generation(new_chromosomes)
        self.chromosomes = new_chromosomes

    def select_best(self):
        return max(self.chromosomes, key=operator.attrgetter("fitness"))

    def next_generation_elitism(self):
        new_chromosomes = [self.select_best()]
        self.fill_next_generation(new_chromosomes)
        self.chromosomes = new_chromosomes

    def sort_descending(self):
        self.chromosomes.sort(key=operator.attrgetter("fitness"), reverse=True)

    def next_generation_steady(self):
        self.sort_descending()

        for _ in range(self.parameters.population_size):
            offspring = self.select_one_offspring()
            if offspring.fitness > self.chromosomes[-1].fitness:
                self.chromosomes[-1] = offspring

    def next_generation(self):
        if self.parameters.generation_type == GenerationType.SIMPLE:
            self.next_generation_simple()
        if self.parameters.generation_type == GenerationType.ELITISM:
            self.next_generation_elitism()
        if self.parameters.generation_type == GenerationType.STEADY:
            self.next_generation_steady()

        self.generation += 1

    def run_generations(self, no_generations):
        for _ in range(no_generations):
            self.next_generation()
            print(self)

    def get_average_fitness(self):
        total = 0

        for ch in self.chromosomes:
            total += ch.fitness

        return total / self.parameters.population_size

    def __str__(self):
        return f"Generation: {self.generation}\n" + \
                f"Population size: {self.parameters.population_size}\n" + \
                f"Best chromosome: {self.select_best()}\n" + \
                f"Average fitness: {self.get_average_fitness()}\n\n"
