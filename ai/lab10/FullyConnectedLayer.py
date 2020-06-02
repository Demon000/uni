import numpy as np

from Layer import Layer


class FullyConnectedLayer(Layer):
    def __init__(self, learning_rate, input_size=None, output_size=None):
        super().__init__()

        self.learning_rate = learning_rate
        self.weights = None
        self.bias = None
        self.input = None
        self.output = None

        self.weights = np.random.rand(input_size, output_size) - 0.5
        self.bias = np.random.rand(1, output_size) - 0.5

    def forward_propagation(self, input_data):
        self.input = input_data
        self.output = np.matmul(self.input, self.weights) + self.bias
        return self.output

    def backward_propagation(self, output_error):
        input_error = np.matmul(output_error, self.weights.T)
        weights_error = np.matmul(self.input.T, output_error)

        self.weights -= weights_error * self.learning_rate
        self.bias -= output_error * self.learning_rate
        return input_error
