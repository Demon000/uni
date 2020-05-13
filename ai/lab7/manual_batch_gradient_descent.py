class ManualBatchGradientDescent:
    def __init__(self, learning_rate):
        self.learning_rate = learning_rate
        self.dependant_betas = []
        self.independent_beta = 0

    def expand_dependant_betas(self, inputs):
        no_betas = len(inputs[0])
        no_current_betas = len(self.dependant_betas)
        if no_betas > no_current_betas:
            for i in range(no_betas - no_current_betas):
                self.dependant_betas.append(0)

    def predict_one(self, i):
        prediction = self.independent_beta
        no_features = len(i)
        for feature_index in range(no_features):
            prediction += self.dependant_betas[feature_index] * i[feature_index]
        return [prediction]

    def fit(self, inputs, outputs):
        self.expand_dependant_betas(inputs)

        no_samples = len(inputs)
        no_features = len(inputs[0])
        for sample_index in range(no_samples):
            i = inputs[sample_index]
            o = outputs[sample_index]
            error = self.predict_one(i)[0] - o[0]

            self.independent_beta -= self.learning_rate * error
            for feature_index in range(no_features):
                self.dependant_betas[feature_index] -= self.learning_rate * error * i[feature_index]

    def predict(self, inputs):
        outputs = []
        for i in inputs:
            o = self.predict_one(i)
            outputs.append(o)
        return outputs
