from sklearn.preprocessing import StandardScaler


class Normalizer:
    def __init__(self):
        self.scaler = StandardScaler()

    def fit(self, inputs):
        self.scaler.fit(inputs)

    @property
    def mean(self):
        return self.scaler.mean_

    @property
    def variance(self):
        return self.scaler.var_

    def transform(self, inputs):
        return self.scaler.transform(inputs, copy=True)
