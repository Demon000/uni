from random import randint, random, choices

from parameters import MutationType, CrossoverType


class Chromosome:
    def __init__(self, parameters):
        self.parameters = parameters
        self._fitness = None

    def evaluate(self):
        self._fitness = self.parameters.fitness_fn(self)

    def invalidate_fitness(self):
        self._fitness = None

    @property
    def fitness(self):
        if self._fitness is None:
            self.evaluate()

        return self._fitness

    def mutate_swap(self):
        raise NotImplementedError()

    def mutate(self):
        if self.parameters.mutation_type == MutationType.SWAP:
            self.mutate_swap()
        else:
            raise Exception("Invalid mutation type")

        self.invalidate_fitness()

    def try_mutate(self):
        if random() > self.parameters.mutation_chance:
            return

        self.mutate()

    def transfer_crossover(self, other):
        raise NotImplementedError()

    def crossover(self, other):
        if self.parameters.crossover_type == CrossoverType.TRANSFER:
            return self.transfer_crossover(other)
        else:
            raise Exception("Invalid crossover type")

    @staticmethod
    def offspring(first, second):
        child = first.crossover(second)
        child.try_mutate()
        return child

    @staticmethod
    def random(parameters):
        raise NotImplementedError()
