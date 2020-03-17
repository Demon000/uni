class TSPCity:
    def __init__(self, index):
        self.index = index
        self.visited = False
        self.parent = None


class TSP:
    def __init__(self, input_path, output_path, first_city_index, last_city_index):
        self.input_path = input_path
        self.output_path = output_path

        with open(input_path, "r") as input:
            self.no_cities = int(input.readline())

            self.cities = set()
            for i in range(self.no_cities):
                city = TSPCity(i)
                if i == first_city_index:
                    self.start_city = city
                if i == last_city_index:
                    self.end_city = city
                self.cities.add(city)

            self.distances = []

            distance_lines = input.readlines()
            for line in distance_lines:
                distances = [int(d) for d in line.split(",")]
                self.distances.append(distances)

    def solve(self):
        visited_cities = []

        last_city = self.start_city
        last_city.visited = True
        total_distance = 0
        cities = 1
        visited_cities.append(last_city)

        while True:
            previous_city = last_city
            last_city, distance = self.find_closest_city(previous_city)
            if last_city is None:
                last_city = previous_city
                break

            last_city.parent = previous_city
            last_city.visited = True
            self.cities.remove(last_city)
            total_distance += distance
            cities += 1
            visited_cities.append(last_city)

            if last_city == self.end_city:
                break

        if self.start_city == self.end_city:
            total_distance += self.get_distance(last_city, self.end_city)

        with open(self.output_path, "w") as file:
            file.write(str(cities))
            file.write("\n")
            file.write(",".join([str(c.index + 1) for c in visited_cities]))
            file.write("\n")
            file.write(str(total_distance))

    def get_distance(self, first_city, second_city):
        return self.distances[first_city.index][second_city.index]

    def find_closest_city(self, first_city):
        min_distance = sys.maxsize
        found_city = None

        for second_city in self.cities:
            if first_city is second_city:
                continue

            distance = self.get_distance(first_city, second_city)
            if distance < min_distance and not second_city.visited:
                min_distance = distance
                found_city = second_city

        return found_city, min_distance


if __name__ == "__main__":
    import sys

    args = sys.argv[1:]

    input_path = args[0]
    output_path = args[1]
    try:
        first_city = args[2]
        last_city = args[3]
    except IndexError:
        first_city = 0
        last_city = 0

    tsp = TSP(input_path, output_path, first_city, last_city)
    tsp.solve()