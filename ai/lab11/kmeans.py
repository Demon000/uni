import numpy as np

from sklearn.metrics import accuracy_score


MAX_SAME_ITERATIONS = 100


class KMeans:
    def __init__(self):
        self.classes = None
        self.centers = None
        self.previous_score = None
        self.same_iterations = 0

    def expand(self, classes, inputs, outputs):
        if self.classes == classes:
            return

        self.classes = classes
        self.centers = {}
        for c in self.classes:
            no_samples = len(inputs)
            for index in range(no_samples):
                i = inputs[index]
                o = outputs[index]

                if c not in self.centers and o == c:
                    self.centers[c] = i

    def predict_one_raw(self, i):
        return {c: np.linalg.norm(i - self.centers[c]) for c in self.classes}

    def predict_one(self, i):
        distances = self.predict_one_raw(i)
        values = list(distances.values())
        keys = list(distances.keys())
        min_value = min(values)
        min_value_index = values.index(min_value)
        return keys[min_value_index]

    def fit(self, inputs, outputs):
        classes = list(set(outputs))
        self.expand(classes, inputs, outputs)

        if self.same_iterations == MAX_SAME_ITERATIONS:
            return

        predicted_outputs = self.predict(inputs)
        classifications = self.predict_classifications(inputs)

        score = accuracy_score(outputs, predicted_outputs)
        score = score if score >= 0.5 else 1 - score

        if self.previous_score != score or not self.previous_score:
            self.previous_score = score
            self.same_iterations = 0
        else:
            self.same_iterations += 1

        for c in self.classes:
            self.centers[c] = np.average(classifications[c], axis=0)

    def predict_classifications(self, inputs):
        classifications = {}
        for c in self.classes:
            classifications[c] = []

        for i in inputs:
            c = self.predict_one(i)
            classifications[c].append(i)

        return classifications

    def predict(self, inputs):
        outputs = []

        for i in inputs:
            c = self.predict_one(i)
            outputs.append(c)

        return outputs
