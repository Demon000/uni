#!/usr/bin/env python3

import ast


def get_vector_product(first_list, second_list):
    p = 0
    for pair in zip(first_list, second_list):
        p += pair[0] * pair[1]

    return p


if __name__ == "__main__":
    import sys

    args = sys.argv[1:]
    first_list = ast.literal_eval(args[0])
    second_list = ast.literal_eval(args[1])
    product = get_vector_product(first_list, second_list)
    print(f"Rare vectors product: {product}")
