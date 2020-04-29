from math import exp, log

from checks import check_same_size


def sigmoid(x):
    return 1 / (1 + exp(-x))


def multi_label_error(predicted_targets, real_targets):
    check_same_size(predicted_targets, real_targets)
    no_samples = len(predicted_targets)

    scaled_predicted_targets = []
    for sample in predicted_targets:
        scaled_predicted_targets.append([])
        for value in sample:
            scaled_predicted_targets[-1].append(sigmoid(value))

    print(scaled_predicted_targets)

    error = 0.0
    for sample_index in range(no_samples):
        for label_probability in scaled_predicted_targets[sample_index]:
            error += log(label_probability)

    return -error / no_samples


pt = [
    [5, 3, 6, 9],
    [3, 5, 9, 9],
    [1, 1, 1, 1],
    [2, 3, 4, 5],
]

rt = [
    [1, 0, 0, 1],
    [0, 1, 1, 1],
    [0, 0, 0, 1],
    [0, 0, 1, 1],
]


print(multi_label_error(pt, rt))
