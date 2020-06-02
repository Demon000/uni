from Layer import Layer


class ActivationLayer(Layer):
    def __init__(self, activation, activation_prime):
        super().__init__()

        self.activation = activation
        self.activation_prime = activation_prime

        self.input = None
        self.output = None

    def forward_propagation(self, input_data):
        self.input = input_data
        self.output = self.activation(self.input)
        return self.output

    def backward_propagation(self, output_error):
        return self.activation_prime(self.input) * output_error
