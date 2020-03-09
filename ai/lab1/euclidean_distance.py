#!/usr/bin/env python3

import math


class Point:
    def __init__(self, x, y):
        self.y = y
        self.x = x

    @staticmethod
    def from_string(str):
        parts = str.split(",")
        x = float(parts[0])
        y = float(parts[1])
        return Point(x, y)

    @staticmethod
    def get_euclidean_distance(first, second):
        return math.sqrt(math.pow(second.x - first.x, 2) + math.pow(second.y - first.y, 2))


if __name__ == "__main__":
    import sys

    args = sys.argv[1:]
    first_point = Point.from_string(args[0])
    second_point = Point.from_string(args[1])
    distance = Point.get_euclidean_distance(first_point, second_point)
    print(f"Euclidean distance between x={first_point.x}, y={second_point.y} "
          f"and x={second_point.x}, y={second_point.y} is {distance}")
