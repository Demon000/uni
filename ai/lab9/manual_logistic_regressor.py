from math import exp


def sigmoid(x):
    return 1 / (1 + exp(-x))


class ManualLogisticRegressor:
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
        return sigmoid(prediction)

    def fit(self, inputs, outputs):
        self.expand_dependant_betas(inputs)

        no_samples = len(inputs)
        no_features = len(inputs[0])
        for sample_index in range(no_samples):
            i = inputs[sample_index]
            o = outputs[sample_index]
            error = self.predict_one(i) - o

            self.independent_beta -= self.learning_rate * error
            for feature_index in range(no_features):
                self.dependant_betas[feature_index] -= self.learning_rate * error * i[feature_index]

    def predict(self, inputs):
        outputs = []
        for i in inputs:
            o = self.predict_one(i)
            outputs.append(o)
        return outputs


class ManualMultiClassLogisticRegressor:
    def __init__(self, learning_rate):
        self.learning_rate = learning_rate
        self.label_regressors = {}

    @property
    def classes(self):
        return list(self.label_regressors.keys())

    def expand_labels(self, labels):
        for label in labels:
            if label in self.label_regressors:
                continue

            self.label_regressors[label] = ManualLogisticRegressor(self.learning_rate)

    def fit(self, inputs, outputs):
        self.expand_labels(outputs)

        for (label, regressor) in self.label_regressors.items():
            ovr_outputs = [1 if o == label else 0 for o in outputs]
            regressor.fit(inputs, ovr_outputs)

    def predict_one_raw(self, i):
        label_outputs = []
        chosen_label_value = 0
        chosen_label = None

        for (label, regressor) in self.label_regressors.items():
            label_output = regressor.predict_one(i)
            label_outputs.append(label_output)

            if label_output > chosen_label_value:
                chosen_label_value = label_output
                chosen_label = label

        return label_outputs, chosen_label

    def predict_probabilities(self, inputs):
        outputs = []
        for i in inputs:
            label_outputs, label = self.predict_one_raw(i)
            outputs.append(label_outputs)

        return outputs

    def predict(self, inputs):
        outputs = []
        for i in inputs:
            label_outputs, label = self.predict_one_raw(i)
            outputs.append(label)

        return outputs
