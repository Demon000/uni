import numpy as np


class ManualLinearModel:
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
        self.betas = [result[0][0], result[1][0], result[2][0]]

    def predict(self, inputs):
        b0 = self.betas[0]
        b1 = self.betas[1]
        b2 = self.betas[2]

        predicted_outputs = []
        for i in inputs:
            x1 = i[0]
            x2 = i[1]
            predicted_output = b0 + b1 * x1 + b2 * x2
            predicted_outputs.append([predicted_output])

        return predicted_outputs
