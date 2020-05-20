from sklearn.linear_model import LogisticRegression


class LogisticRegressor:
    def __init__(self):
        self.regressor = LogisticRegression(multi_class='ovr')

    @property
    def classes(self):
        return self.regressor.classes_

    def fit(self, inputs, outputs):
        self.regressor.fit(inputs, outputs)

    def predict(self, inputs):
        return self.regressor.predict(inputs).tolist()

    def predict_probabilities(self, inputs):
        return self.regressor.predict_proba(inputs).tolist()
