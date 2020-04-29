from math import sqrt

from checks import check_same_size


def mt_error_rmse(predicted_targets, real_targets):
    check_same_size(predicted_targets, real_targets)
    no_samples = len(predicted_targets)

    no_targets = len(predicted_targets[0])
    for i in range(len(predicted_targets)):
        assert len(predicted_targets[i]) == no_targets
        assert len(real_targets[i]) == no_targets

    target_errors = [0.0 for _ in range(no_targets)]
    for sample_index in range(no_samples):
        for target_index in range(no_targets):
            target_errors[target_index] += (real_targets[sample_index][target_index] -
                                            predicted_targets[sample_index][target_index]) ** 2

    for target_index in range(no_targets):
        target_errors[target_index] = sqrt(target_errors[target_index]) / no_samples

    return target_errors


pt = [
    [12, 9.5, 9.5],
    [5, 7.5, 8],
    [10.05, 8.2, 8.5],
    [3, 3.7, 3.2],
    [4.5, 5, 6.5],
    [7.555, 6, 3],
]
rt = [
    [11.75, 9.2, 9.3],
    [5.12, 7.6, 8.3],
    [10.06, 8, 8.25],
    [3, 3.3, 3.3],
    [4.3, 5, 6.3],
    [7.6, 5.5, 5],
]

errors = mt_error_rmse(pt, rt)
print(errors)
