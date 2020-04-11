inversion_seq_permutation_map = {}


def get_permutation(inversion_seq):
    inversion_seq_tup = tuple(inversion_seq)
    if inversion_seq_tup in inversion_seq_permutation_map:
        return inversion_seq_permutation_map[inversion_seq_tup]

    length = len(inversion_seq)
    positions = list(range(length))
    permutation = [-1 for _ in range(length)]

    for i in range(length):
        target_free_element = inversion_seq[i]
        position = positions.pop(target_free_element)
        permutation[position] = i

    inversion_seq_permutation_map[inversion_seq_tup] = permutation

    return permutation
