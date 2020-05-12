from math import log, exp

from checks import check_same_size


def soft_max(values):
    exp_values = [exp(value) for value in values]
    sum_exp_values = sum(exp_values)
    scaled_values = []

    for exp_value in exp_values:
        scaled_values.append(exp_value / sum_exp_values)

    return scaled_values


def mc_error(predicted_targets, real_targets):
    check_same_size(predicted_targets, real_targets, False)
    no_samples = len(predicted_targets)

    scaled_predicted_targets = []
    for sample in predicted_targets:
        scaled_predicted_targets.append(soft_max(sample))

    error = 0
    for sample_index in range(no_samples):
        real_class = real_targets[sample_index]
        error += log(scaled_predicted_targets[sample_index][real_class])

    return -error / no_samples


pt = [
    [10, 40, 30, 20, 30],
    [33, 33, 33, 1, 50],
    [90, 10, 0, 0, 20],
    [11, 22, 33, 34],
    [30, 90, 30, 40],
    [15, 25, 45, 15],
]

rt = [
    1,
    2,
    0,
    3,
    1,
    2,
    4,
]

print(mc_error(pt, rt))
