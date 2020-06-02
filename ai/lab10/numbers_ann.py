from math import sqrt, ceil

import numpy as np
import matplotlib.pyplot as plt

from ActivationLayer import ActivationLayer
from FullyConnectedLayer import FullyConnectedLayer
from Network import Network
from math_utils import sigmoid_der, sigmoid, mse_prime

from keras.datasets import mnist
from keras.utils import np_utils

from model_utils import read_model_from_file, save_model_to_file

np.random.seed(5)

NO_TRAINING_SAMPLES = 1000
NO_TEST_SAMPLES = 100
READ_MODEL_FROM_FILE = True
MODEL_FILE_PATH = 'numbers.model'
NO_ITERATIONS = 100
LEARNING_RATE = 0.1

(original_training_inputs, original_training_outputs), \
        (original_test_inputs, original_test_outputs) = mnist.load_data()


def convert(inputs, outputs):
    inputs = inputs.reshape(inputs.shape[0], 1, 28 * 28)
    inputs = inputs.astype('float32')
    inputs /= 255
    return inputs, np_utils.to_categorical(outputs)


all_training_inputs, all_training_outputs = convert(original_training_inputs, original_training_outputs)
all_test_inputs, all_test_outputs = convert(original_test_inputs, original_test_outputs)

all_training_inputs = all_training_inputs[:NO_TRAINING_SAMPLES]
all_training_outputs = all_training_outputs[:NO_TRAINING_SAMPLES]

all_test_inputs = all_test_inputs[:NO_TEST_SAMPLES]
all_test_outputs = all_test_outputs[:NO_TEST_SAMPLES]

if READ_MODEL_FROM_FILE:
    nn = read_model_from_file(MODEL_FILE_PATH)
else:
    nn = Network(layers=[
        FullyConnectedLayer(LEARNING_RATE, input_size=28 * 28, output_size=128),  # input layer
        ActivationLayer(sigmoid, sigmoid_der),
        FullyConnectedLayer(LEARNING_RATE, input_size=128, output_size=64),  # hidden layer
        ActivationLayer(sigmoid, sigmoid_der),
        FullyConnectedLayer(LEARNING_RATE, input_size=64, output_size=10),  # hidden layer
        ActivationLayer(sigmoid, sigmoid_der),
    ], loss=mse_prime)

    for i in range(NO_ITERATIONS):
        nn.fit(all_training_inputs, all_training_outputs)
        print(f"Iteration: {i}/{NO_ITERATIONS}")

    save_model_to_file(MODEL_FILE_PATH, nn)

all_predicted_outputs = nn.predict(all_test_inputs)

NO_ROWS = NO_COLUMNS = ceil(sqrt(NO_TEST_SAMPLES))
fig, axes = plt.subplots(NO_ROWS, NO_COLUMNS, figsize=(20, 20))
for index in range(NO_TEST_SAMPLES):
    predicted_o = all_predicted_outputs[index][0]
    predicted_class = np.argmax(predicted_o)
    o = all_test_outputs[index]
    real_class = np.argmax(o)

    row = index // NO_ROWS
    column = index % NO_COLUMNS
    ax = axes[row][column]
    if predicted_class == real_class:
        color = 'gray'
    else:
        color = 'copper'

    ax.imshow(original_test_inputs[index], cmap=color)
    ax.set_title(f'Real: {real_class}\nPredicted: {predicted_class}')
    ax.axis('off')

plt.show()
