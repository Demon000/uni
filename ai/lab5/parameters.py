from enum import Enum


class GraphType(Enum):
    STATIC = 1
    DYNAMIC = 2


class Parameters:
    def __init__(self, **kwargs):
        self.graph_type = kwargs.get("graph_type", GraphType.STATIC)
        self.graph_reset_chance = kwargs.get("graph_reset_chance", 0)
        self.graph_highway_chance = kwargs.get("graph_highway_chance", 0)
        self.graph_highway_length = kwargs.get("graph_highway_length", 0)
        self.graph_roadblock_chance = kwargs.get("graph_roadblock_chance", 0)
        self.graph_roadblock_length = kwargs.get("graph_roadblock_length", 0)
        self.graph_quarantine_chance = kwargs.get("graph_quarantine_chance", 0)
        self.no_ants = kwargs.get("no_ants", 30)
        self.elite_ants_percentage = kwargs.get("elite_ants_percentage", 0.1)
        self.pheromones_importance = kwargs.get("pheromones_importance", 1)
        self.pheromones_leave_quantity = kwargs.get("pheromones_leave_quantity", 1)
        self.pheromones_evaporation_rate = kwargs.get("pheromones_evaporation_rate", 0.03)
        self.weight_importance = kwargs.get("weight_importance", 3)
        self.graph = None

        self.no_elite_ants = int(self.no_ants * self.elite_ants_percentage)
