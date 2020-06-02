import numpy as np


def tanh(x):
    return np.tanh(x)


def tanh_der(x):
    return 1 - np.tanh(x) ** 2


def sigmoid(a):
    return 1 / (1 + np.exp(-a))


def sigmoid_der(x):
    return sigmoid(x) * (1 - sigmoid(x))


def mse(outputs, outputs_predicted):
    return np.mean(np.power(outputs - outputs_predicted, 2))


def mse_prime(outputs, outputs_predicted):
    return 2 * (outputs_predicted - outputs) / outputs.size
