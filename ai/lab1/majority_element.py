#!/usr/bin/env python3


import ast


if __name__ == "__main__":
    import sys

    args = sys.argv[1:]
    elements = ast.literal_eval(args[0])

    possible_element = None
    possible_element_count = 0
    for element in elements:
        if possible_element_count == 0:
            possible_element = element
            possible_element_count = 1
        elif possible_element == element:
            possible_element_count += 1
        else:
            possible_element_count -= 1

    print(f"Majority element: {possible_element}")
