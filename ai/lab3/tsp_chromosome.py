from random import randint, random, sample

from chromosome import Chromosome
from utils import get_permutation


class TspChromosome(Chromosome):
    def __init__(self, inversion_seq, parameters):
        super().__init__(parameters)

        self.inversion_seq = inversion_seq

    def calculate_fitness(self, inversion_seq):
        permutation = get_permutation(inversion_seq)
        first_element = permutation[0]
        permutation.append(first_element)

        total_distance = 0
        for first_index in range(self.parameters.no_genes):
            second_index = first_index + 1
            first_node = permutation[first_index]
            second_node = permutation[second_index]
            total_distance += self.parameters.graph.distances[first_node][second_node]

        return total_distance

    def evaluate(self):
        return self.calculate_fitness(self.inversion_seq)

    def get_random_inversion(self, index):
        return randint(0, self.parameters.no_genes - index - 1)

    def mutate(self, mutation_chance=None):
        if mutation_chance is None:
            mutation_chance = self.parameters.mutation_chance

        # if self.parameters.debug:
        #     print(f"before: {self}")

        changed = False
        for i in range(self.parameters.no_genes):
            if random() > mutation_chance:
                continue

            changed = True
            self.inversion_seq[i] = self.get_random_inversion(i)

        if changed:
            self.invalidate_fitness()

        # if self.parameters.debug:
        #     print(f"after: {self}")

        return changed

    def crossover(self, other):
        first_inversion_seq = self.inversion_seq[:]
        second_inversion_seq = other.inversion_seq[:]

        crossover_points = sample(range(self.parameters.no_genes), k=self.parameters.no_crossover_points)
        crossover_points_len = len(crossover_points)

        crossover_points.sort()

        total_length = 0
        while crossover_points_len > 0:
            second_point = crossover_points.pop()
            first_point = crossover_points.pop()
            total_length += second_point - first_point
            crossover_points_len -= 2

            for i in range(first_point, second_point):
                first_inversion_seq[i], second_inversion_seq[i] = second_inversion_seq[i], first_inversion_seq[i]

        first_chromosome = TspChromosome(first_inversion_seq, self.parameters)
        first_chromosome.mutate()

        second_chromosome = TspChromosome(second_inversion_seq, self.parameters)
        second_chromosome.mutate()

        return [first_chromosome, second_chromosome]

    def __str__(self):
        return f"Chromosome -> fitness: {self.fitness}, inversion sequence: {self.inversion_seq}"

    @staticmethod
    def random(parameters):
        inversion_seq = []
        for i in range(parameters.no_genes):
            value = randint(0, parameters.no_genes - i - 1)
            inversion_seq.append(value)

        return TspChromosome(inversion_seq, parameters)
