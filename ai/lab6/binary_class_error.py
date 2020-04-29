from math import log

from checks import check_same_size


def bc_error_log_loss(computed_bc_probability, real_bc):
    check_same_size(computed_bc_probability, real_bc)
    no_samples = len(computed_bc_probability)

    error = 0.0
    for index in range(no_samples):
        true_probability = computed_bc_probability[index]
        real_value = real_bc[index]
        error += real_value * log(true_probability) + (1 - real_value) * log(1 - true_probability)

    return -error / no_samples


cbc = [
    0.25,
    0.7,
    0.75,
    0.6,
    0.1,
]

rbc = [
    0,
    1,
    1,
    1,
    0,
]

print(bc_error_log_loss(cbc, rbc))

