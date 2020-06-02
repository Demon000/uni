from math import sqrt, ceil

import numpy as np
import matplotlib.pyplot as plt

from ActivationLayer import ActivationLayer
from FullyConnectedLayer import FullyConnectedLayer
from Network import Network
from math_utils import sigmoid_der, sigmoid, mse_prime

from model_utils import read_model_from_file, save_model_to_file
from sepia_utils import sepia_load_data

np.random.seed(5)

READ_MODEL_FROM_FILE = True
MODEL_FILE_PATH = 'sepia.model'
NO_ITERATIONS = 10
LEARNING_RATE = 0.1

original_inputs, original_outputs = sepia_load_data()


def convert(inputs):
    inputs = inputs.reshape(inputs.shape[0], 1, 50 * 50 * 3)
    return inputs


all_inputs = convert(original_inputs)
all_outputs = original_outputs

all_training_inputs = all_inputs
all_training_outputs = all_outputs
all_test_inputs = all_inputs
all_test_outputs = all_outputs

if READ_MODEL_FROM_FILE:
    nn = read_model_from_file(MODEL_FILE_PATH)
else:
    nn = Network(layers=[
        FullyConnectedLayer(LEARNING_RATE, input_size=50 * 50 * 3, output_size=128),  # input layer
        ActivationLayer(sigmoid, sigmoid_der),
        FullyConnectedLayer(LEARNING_RATE, input_size=128, output_size=64),  # hidden layer
        ActivationLayer(sigmoid, sigmoid_der),
        FullyConnectedLayer(LEARNING_RATE, input_size=64, output_size=1),  # hidden layer
        ActivationLayer(sigmoid, sigmoid_der),
    ], loss=mse_prime)

    for i in range(NO_ITERATIONS):
        nn.fit(all_training_inputs, all_training_outputs)
        print(f"Iteration: {i + 1}/{NO_ITERATIONS}")

    save_model_to_file(MODEL_FILE_PATH, nn)

all_predicted_outputs = nn.predict(all_inputs)

NO_TEST_SAMPLES = len(all_inputs)
NO_ROWS = NO_COLUMNS = ceil(sqrt(NO_TEST_SAMPLES))
fig, axes = plt.subplots(NO_ROWS, NO_COLUMNS, figsize=(50, 50))
for index in range(NO_TEST_SAMPLES):
    predicted_is_sepia = all_predicted_outputs[index][0][0]
    real_is_sepia = all_test_outputs[index][0]
    image = original_inputs[index]

    row = index // NO_ROWS
    column = index % NO_COLUMNS
    ax = axes[row][column]

    if round(predicted_is_sepia) != real_is_sepia:
        ax.imshow(image[:, :, 0], cmap='Reds_r')
    else:
        ax.imshow(image)

    ax.set_title(f'Real: {real_is_sepia}\nPredicted: {predicted_is_sepia}')
    ax.axis('off')

plt.show()
