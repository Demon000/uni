#!/usr/bin/env python3


class Node:
    CHILDREN_SIZE = 26

    def __init__(self):
        self.children = [None] * self.CHILDREN_SIZE
        self.built_word = None
        self.occurrences = 0

    def add(self, partial_word, built_word=""):
        index = ord(partial_word[0]) - ord("a")
        if self.children[index] is None:
            node = self.children[index] = Node()
        else:
            node = self.children[index]

        new_built_word = built_word + partial_word[0]
        if len(partial_word) == 1:
            node.occurrences += 1
            node.built_word = new_built_word
            return node
        elif len(partial_word) >= 1:
            return node.add(partial_word[1:], new_built_word)


if __name__ == "__main__":
    import sys

    args = sys.argv[1:]
    words = args[0].split(" ")
    target_occurrences = int(args[1])

    root_node = Node()
    final_nodes = [root_node.add(word) for word in words]
    filtered_nodes = [node for node in final_nodes if node.occurrences == target_occurrences]
    for final_node in filtered_nodes:
        print(final_node.built_word)
