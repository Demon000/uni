import pandas as pd
import numpy as np

from sklearn.metrics import classification_report

from ActivationLayer import ActivationLayer
from FullyConnectedLayer import FullyConnectedLayer
from Network import Network
from math_utils import sigmoid_der, sigmoid, mse_prime

np.random.seed(5)

data = pd.read_csv('iris.data')
all_inputs = data[['SepalLengthCm', 'SepalWidthCm', 'PetalLengthCm', 'PetalWidthCm']]
named_all_outputs = data['Species']

classes = ['Iris-setosa', 'Iris-versicolor', 'Iris-virginica']
no_classes = len(classes)
all_inputs = all_inputs.apply(lambda x: (x - x.min()) / (x.max() - x.min()))
all_outputs = named_all_outputs.replace(classes, range(no_classes))

all_inputs = all_inputs.values
all_outputs = all_outputs.values

class_maps = [[[1, 0, 0]], [[0, 1, 0]], [[0, 0, 1]]]
all_inputs = np.array([[i] for i in all_inputs])
all_outputs = np.array([class_maps[o][:] for o in all_outputs])

# all_training_inputs, all_test_inputs, all_training_outputs, all_test_outputs = \
#     train_test_split(all_inputs, all_outputs, test_size=0.2)

all_training_inputs = all_inputs
all_test_inputs = all_inputs
all_training_outputs = all_outputs
all_test_outputs = all_outputs

LEARNING_RATE = 0.01
nn = Network(layers=[
    FullyConnectedLayer(LEARNING_RATE, input_size=4, output_size=16),  # input layer
    ActivationLayer(sigmoid, sigmoid_der),
    FullyConnectedLayer(LEARNING_RATE, input_size=16, output_size=3),  # hidden layer
    ActivationLayer(sigmoid, sigmoid_der),
], loss=mse_prime)

ITERATIONS = 1000
for i in range(ITERATIONS):
    nn.fit(all_training_inputs, all_training_outputs)
    all_predicted_outputs = nn.predict(all_test_inputs)
    predicted_outputs = []
    for o in all_predicted_outputs:
        predicted_outputs.append(np.argmax(o[0]))

    test_outputs = []
    for o in all_test_outputs:
        test_outputs.append(np.argmax(o[0]))

    print(classification_report(test_outputs, predicted_outputs))
