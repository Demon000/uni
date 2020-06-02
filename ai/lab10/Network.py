class Network:
    def __init__(self, layers, loss):
        self.layers = layers
        self.loss_prime = loss

    def predict_one(self, i):
        last_output = i
        for layer in self.layers:
            last_output = layer.forward_propagation(last_output)
        return last_output

    def adjust_one(self, predicted_o, o):
        error = self.loss_prime(o, predicted_o)
        for layer in reversed(self.layers):
            error = layer.backward_propagation(error)

    def fit_one(self, i, o):
        predicted_o = self.predict_one(i)
        self.adjust_one(predicted_o, o)

    def fit(self, inputs, outputs):
        no_samples = len(inputs)
        for index in range(no_samples):
            i = inputs[index]
            o = outputs[index]
            self.fit_one(i, o)

    def predict(self, inputs):
        outputs = []
        for i in inputs:
            o = self.predict_one(i)
            outputs.append(o)
        return outputs
