#!/usr/bin/env python3

import ast

if __name__ == "__main__":
    import sys

    args = sys.argv[1:]
    numbers = ast.literal_eval(args[0])
    occurrences = {}

    for number in numbers[1:]:
        numbers[0] ^= number

    x = 1
    for i in range(2, len(numbers)):
        x ^= i

    print(f"Number repeating is: {numbers[0] ^ x}")
