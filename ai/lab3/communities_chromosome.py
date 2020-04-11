from random import choices, randint

from chromosome import Chromosome


class CommunitiesChromosome(Chromosome):
    def __init__(self, communities, parameters):
        super().__init__(parameters)

        self.communities = communities
        self.no_communities = 0

    def evaluate(self):
        graph = self.parameters.graph
        two_m = 2 * graph.no_edges
        q = 0.0

        for first_index in graph.nodes:
            first_degree = graph.degrees[first_index]
            first_community = self.communities[first_index]
            for second_index in graph.nodes:
                second_degree = graph.degrees[second_index]
                second_community = self.communities[second_index]

                adjacency = 1 if graph.adjacency[first_index][second_index] else 0

                if first_community == second_community:
                    q += adjacency - first_degree * second_degree / two_m

        return q / two_m

    def random_community_index(self):
        return randint(0, self.parameters.no_genes - 1)

    def random_community(self):
        return self.communities[self.random_community_index()]

    def normalize_communities(self):
        replacements = {}
        gene_values_iter = iter(self.parameters.gene_values)
        used_values = 0

        for i in range(self.parameters.no_genes):
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

    def transfer_crossover(self, other):
        self.normalize_communities()
        other.normalize_communities()
        transferred_community = self.random_community()
        new_communities = [x if x == transferred_community else y
                           for x, y in zip(self.communities, other.communities)]
        new_chromosome = CommunitiesChromosome(new_communities, self.parameters)
        return [new_chromosome]

    def __str__(self):
        return f"Chromosome -> fitness: {self.fitness}, no_communities: {self.no_communities}"

    @staticmethod
    def random(parameters):
        communities = choices(parameters.gene_values, k=parameters.no_genes)
        chromosome = CommunitiesChromosome(communities, parameters)
        return chromosome
