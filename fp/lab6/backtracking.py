def recursive(solutions, solution, n):
    '''
    Generate all the sequences of length n formed out of -1, 0, 1,
    so that the first member and the last member of the sequence are 0,
    and the difference of consecutive members is either 1 or 2.

    Args:
        solutions (list): The list in which the final sequences are put.
        solution (list): The current sequence.
        n (list): The number of members the final sequence must have.
    '''
    if len(solution) == n:
        solution_copy = solution[:]
        solutions.append(solution_copy)
        return

    for value in range(-1, 2):
        if len(solution) == 0 and value != 0:
            continue

        if len(solution) == n - 1 and value != 0:
            continue

        if len(solution) and value == solution[-1]:
            continue

        solution.append(value)
        recursive(solutions, solution, n)
        solution.pop()

def iterative(solutions, solution, n):
    '''
    Generate all the sequences of length n formed out of -1, 0, 1,
    so that the first member and the last member of the sequence are 0,
    and the difference of consecutive members is either 1 or 2.

    Args:
        solutions (list): The list in which the final sequences are put.
        solution (list): The current sequence.
        n (list): The number of members the final sequence must have.
    '''
    solution.append(-1)

    while True:
        is_consistent = False
        is_exhausted = False

        while not is_consistent:
            if solution[-1] > 0:
                is_exhausted = True
                break

            solution[-1] += 1

            if len(solution) == n and solution[-1] != 0:
                continue

            if len(solution) == 1 and solution[-1] != 0:
                continue

            if len(solution) > 1 and solution[-1] == solution[-2]:
                continue

            is_consistent = True

        if is_consistent:
            if len(solution) == n:
                solution_copy = solution[:]
                solutions.append(solution_copy)
            else:
                solution.append(-2)
        elif is_exhausted:
            solution = solution[:-1]

        if not len(solution):
            break

def generate_solutions(fn, n):
    '''
    Generate all the sequences of length 2 * n + 1 formed out of -1, 0, 1,
    so that the first member and the last member of the sequence are 0,
    and the difference of consecutive members is either 1 or 2.

    Args:
        fn (function): The function to use for generating the sequences.
        n (list): The number to use when determining the length a final
            sequence must have.

    Returns:
        list: The generated list of sequences.
    '''
    solutions = []
    fn(solutions, [], 2 * n + 1)
    return solutions

def print_solutions(solutions):
    '''
    Print the sequences.

    solutions (list): The list of sequences to print.
    '''
    for solution in solutions:
        print(solution)

'''
Candidate solution: x = (x0, x1, ..., x2*k+1), xi ∈ (-1, 0, 1)
Consistent solution: x = (x0, x1, ..., x2*k+1) consistent if |xi+1 - xi| ∈ (1, 2)
Solution condition x = (x0, x1, ..., xk) solution if consistent and k = 2 * n + 1
'''

n = int(input())

solutions = generate_solutions(recursive, n)
print_solutions(solutions)

print()

solutions = generate_solutions(iterative, n)
print_solutions(solutions)
