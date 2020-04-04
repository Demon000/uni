from random import choices, randint

from chromosome import Chromosome


class CommunitiesChromosome(Chromosome):
    def __init__(self, communities, parameters):
        super().__init__(parameters)

        self.communities = communities
        self.no_communities = 0

    def random_community_index(self):
        return randint(0, len(self.communities) - 1)

    def random_community(self):
        return self.communities[self.random_community_index()]

    def normalize_communities(self):
        replacements = {}
        gene_values_iter = iter(self.parameters.gene_values)
        used_values = 0

        for i in range(len(self.communities)):
            e = self.communities[i]

            if e not in replacements:
                replacements[e] = next(gene_values_iter)
                used_values += 1

            self.communities[i] = replacements[e]

        self.no_communities = used_values

    def mutate_swap(self):
        self.normalize_communities()
        first_index = self.random_community_index()
        second_index = self.random_community_index()
        self.communities[first_index], self.communities[second_index] = \
            self.communities[second_index], self.communities[first_index]

    def __str__(self):
        return f"Chromosome -> fitness: {self.fitness}, no_communities: {self.no_communities}"

    def transfer_crossover(self, other):
        self.normalize_communities()
        other.normalize_communities()
        transferred_community = self.random_community()
        new_communities = [x if x == transferred_community else y
                           for x, y in zip(self.communities, other.communities)]
        return CommunitiesChromosome(new_communities, self.parameters)

    @staticmethod
    def random(parameters):
        communities = choices(parameters.gene_values, k=parameters.no_genes)
        chromosome = CommunitiesChromosome(communities, parameters)
        return chromosome
