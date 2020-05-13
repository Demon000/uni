from sklearn.linear_model import SGDRegressor


class BatchGradientDescent:
    def __init__(self, learning_rate):
        self.regressor = SGDRegressor(learning_rate='constant', eta0=learning_rate)

    def fit(self, inputs, outputs):
        outputs = [o[0] for o in outputs]
        self.regressor.partial_fit(inputs, outputs)

    def predict(self, inputs):
        predicted_outputs = self.regressor.predict(inputs)
        return [[o] for o in predicted_outputs]
