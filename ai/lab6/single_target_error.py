from checks import check_same_size


def st_error_mae(predicted_targets, real_targets):
    check_same_size(predicted_targets, real_targets)
    no_samples = len(predicted_targets)

    error = 0.0
    for sample_index in range(no_samples):
        error += abs(real_targets[sample_index] - predicted_targets[sample_index])

    return error / no_samples


pt = [12, 5, 10.05, 3, 4.5, 7.555]
ct = [11.75, 5.12, 10.06, 3, 4.3, 7.6]

print(st_error_mae(pt, ct))
