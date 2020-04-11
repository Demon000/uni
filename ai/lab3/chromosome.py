class Chromosome:
    def __init__(self, parameters):
        self.parameters = parameters
        self._fitness = None

    def evaluate(self):
        raise NotImplementedError()

    def invalidate_fitness(self):
        self._fitness = None

    @property
    def fitness(self):
        if self._fitness is None:
            self._fitness = self.evaluate()

        return self._fitness

    def mutate(self):
        raise NotImplementedError()

    def crossover(self, other):
        raise NotImplementedError()

    @staticmethod
    def offsprings(first, second):
        return first.crossover(second)

    @staticmethod
    def random(parameters):
        raise NotImplementedError()
