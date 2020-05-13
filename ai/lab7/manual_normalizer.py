from statistics import stdev


class ManualNormalizer:
    def __init__(self):
        self._means = None
        self._st_deviations = None

    def fit(self, inputs):
        self._means = []
        self._st_deviations = []

        no_samples = len(inputs)
        no_features = len(inputs[0])
        for feature_index in range(no_features):
            samples_column = inputs[:][feature_index]
            self._means.append(sum(samples_column) / no_samples)
            self._st_deviations.append(stdev(samples_column))

    @property
    def mean(self):
        return self._means

    @property
    def variance(self):
        return self._st_deviations

    def transform(self, inputs):
        results = []

        no_features = len(inputs[0])
        for i in inputs:
            results.append([])
            for feature_index in range(no_features):
                r = (i[feature_index] - self._means[feature_index]) / self._st_deviations[feature_index]
                results[-1].append(r)

        return results
