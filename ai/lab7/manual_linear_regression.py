import numpy as np


class ManualLinearRegression:
    def __init__(self):
        self.betas = None

    def fit(self, inputs, outputs):
        matrix = np.array(inputs)
        matrix = np.insert(matrix, 0, 1, axis=1)
        transposed = np.transpose(matrix)
        multiplied = np.matmul(transposed, matrix)
        inverted_matrix = np.linalg.inv(multiplied)
        result = np.matmul(inverted_matrix, transposed)
        result = np.matmul(result, outputs)

        self.betas = []
        for line in result:
            self.betas.append(line[0])

    def predict(self, inputs):
        no_betas = len(self.betas)
        b0 = self.betas[0]

        predicted_outputs = []
        for i in inputs:
            predicted_output = b0

            for beta_index in range(1, no_betas):
                predicted_output += self.betas[beta_index] * i[beta_index - 1]

            predicted_outputs.append([predicted_output])

        return predicted_outputs
