import csv
import os
from random import shuffle
import matplotlib.pyplot as plt
import numpy as np
from sklearn.linear_model import LinearRegression

from manual_linear_regression import ManualLinearRegression

HAPPINESS_COLUMN = 2
GDP_COLUMN = 5
FREEDOM_COLUMN = 8


def load_data(file_path):
    data = []
    with open(file_path) as file:
        csv_reader = csv.reader(file, delimiter=",")
        for row in csv_reader:
            data.append(row)

    inputs = [[float(line[GDP_COLUMN]), float(line[FREEDOM_COLUMN])] for line in data]
    outputs = [[float(line[HAPPINESS_COLUMN])] for line in data]

    return inputs, outputs


def split_training_set(inputs, outputs, percent_training):
    training_inputs = []
    training_outputs = []
    test_inputs = []
    test_outputs = []
    no_samples = len(inputs)

    indices = list(range(no_samples))
    shuffle(indices)

    training_samples_left = int(percent_training * no_samples)
    for i in indices:
        if training_samples_left > 0:
            training_inputs.append(inputs[i])
            training_outputs.append(outputs[i])
            training_samples_left -= 1
        else:
            test_inputs.append(inputs[i])
            test_outputs.append(outputs[i])

    return training_inputs, training_outputs, test_inputs, test_outputs


def calculate_loss(predicted_outputs, expected_outputs):
    no_samples = len(expected_outputs)

    loss_sum = 0
    for i in range(no_samples):
        expected = expected_outputs[i][0]
        predicted = predicted_outputs[i][0]
        loss_sum += (expected - predicted) ** 2

    return loss_sum


def plot_scatter(ax, inputs, outputs, color):
    x_line = [i[0] for i in inputs]
    y_line = [i[1] for i in inputs]
    z_line = [o[0] for o in outputs]
    ax.scatter3D(x_line, y_line, z_line, color)


def plot(training_inputs, training_outputs, test_inputs, test_outputs, predicted_outputs):
    plt.figure()
    ax = plt.axes(projection="3d")

    plot_scatter(ax, training_inputs, training_outputs, "red")
    plot_scatter(ax, test_inputs, test_outputs, "blue")

    min_index = np.argmin(predicted_outputs)
    max_index = np.argmax(predicted_outputs)

    xs = [test_inputs[min_index][0], test_inputs[max_index][0]]
    ys = [test_inputs[min_index][1], test_inputs[max_index][1]]
    zs = [predicted_outputs[min_index][0], predicted_outputs[max_index][0]]
    ax.plot(xs, ys, zs)

    ax.set_xlabel("GDP")
    ax.set_ylabel("Freedom")
    ax.set_zlabel("Happiness")
    plt.show()


def run(model, training_inputs, training_outputs, test_inputs, test_outputs, method="manual"):
    model.fit(training_inputs, training_outputs)
    predicted_outputs = model.predict(test_inputs)

    loss = calculate_loss(predicted_outputs, test_outputs)

    # print(f"Predicted: {predicted_outputs}")
    # print(f"Expected: {test_outputs}")
    print(f"Loss: {loss}")

    plot(training_inputs, training_outputs, test_inputs, test_outputs, predicted_outputs)


__location__ = os.path.realpath(os.path.join(os.getcwd(), os.path.dirname(__file__)))
csv_2017_path = os.path.join(__location__, "2017.csv")
all_inputs, all_outputs = load_data(csv_2017_path)

all_training_inputs, all_training_outputs, all_test_inputs, all_test_outputs = \
    split_training_set(all_inputs, all_outputs, 0.8)

linear_model = ManualLinearRegression()
run(linear_model, all_inputs, all_outputs, all_inputs, all_outputs)
run(linear_model, all_training_inputs, all_training_outputs, all_test_inputs, all_test_outputs)

linear_model = LinearRegression()
run(linear_model, all_inputs, all_outputs, all_inputs, all_outputs)
run(linear_model, all_training_inputs, all_training_outputs, all_test_inputs, all_test_outputs)
