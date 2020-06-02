class Layer:
    def forward_propagation(self, input_data):
        raise NotImplementedError()

    def backward_propagation(self, output_error):
        raise NotImplementedError()
