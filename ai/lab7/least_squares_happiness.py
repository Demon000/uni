import csv
import os
from random import shuffle
import matplotlib.pyplot as plt
import numpy as np
from sklearn.linear_model import LinearRegression

from batch_gradient_descent import BatchGradientDescent
from manual_batch_gradient_descent import ManualBatchGradientDescent
from manual_linear_regression import ManualLinearRegression
from manual_normalizer import ManualNormalizer
from normalizer import Normalizer


def load_data(file_path, input_column_indices, output_column_index):
    data = []
    with open(file_path) as file:
        csv_reader = csv.reader(file, delimiter=",")
        for row in csv_reader:
            data.append(row)

    inputs = []
    outputs = []
    for line in data:
        input_values = []
        for input_column_index in input_column_indices:
            input_values.append(float(line[input_column_index]))

        inputs.append(input_values)

        outputs.append([float(line[output_column_index])])

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


def plot_predicted_outputs(training_inputs, training_outputs, test_inputs, test_outputs, predicted_outputs, labels):
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

    ax.set_xlabel(labels[0])
    ax.set_ylabel(labels[1])
    ax.set_zlabel(labels[2])
    plt.show()


def plot_losses(losses):
    plt.plot(range(len(losses)), losses)
    plt.xlabel("Iteration")
    plt.ylabel("Loss")
    plt.title(losses[-1])


def run(model, normalizer, training_inputs, training_outputs,
        test_inputs, test_outputs, labels=None, iterations=1):
    last_predicted_outputs = None
    last_loss = None
    losses = []

    normalizer.fit(training_inputs)

    training_inputs = normalizer.transform(training_inputs)
    test_inputs = normalizer.transform(test_inputs)

    for i in range(iterations):
        model.fit(training_inputs, training_outputs)
        last_predicted_outputs = model.predict(test_inputs)
        last_loss = calculate_loss(last_predicted_outputs, test_outputs)
        losses.append(last_loss)

    # print(f"Predicted: {predicted_outputs}")
    # print(f"Expected: {test_outputs}")
    print(f"Mean: {normalizer.mean}")
    print(f"Variance: {normalizer.variance}")
    print(f"Loss: {last_loss}")

    if iterations != 1:
        plot_losses(losses)

    if len(training_inputs[0]) == 2 and len(training_outputs[0]) == 1 and \
            labels is not None and len(labels) == 3:
        plot_predicted_outputs(training_inputs, training_outputs, test_inputs, test_outputs, last_predicted_outputs,
                               labels)


def run_both(model, normalizer, inputs, outputs,
             training_inputs, training_outputs,
             test_inputs, test_outputs, labels, iterations=1):
    run(model, normalizer, inputs, outputs, inputs, outputs, labels, iterations)
    run(model, normalizer, training_inputs, training_outputs, test_inputs, test_outputs, labels, iterations)


__location__ = os.path.realpath(os.path.join(os.getcwd(), os.path.dirname(__file__)))

HAPPINESS_COLUMN = 2
GDP_COLUMN = 5
FREEDOM_COLUMN = 8
TRUST_COLUMN = 10

input_columns = [GDP_COLUMN, FREEDOM_COLUMN]
output_column = HAPPINESS_COLUMN
all_labels = ["GDP", "Freedom", "Happiness"]

csv_2017_path = os.path.join(__location__, "2017.csv")
all_inputs, all_outputs = load_data(csv_2017_path, input_columns, output_column)

all_training_inputs, all_training_outputs, all_test_inputs, all_test_outputs = \
    split_training_set(all_inputs, all_outputs, 0.8)

# run_both(ManualLinearRegression(), Normalizer(), all_inputs, all_outputs,
#          all_training_inputs, all_training_outputs,
#          all_test_inputs, all_test_outputs, all_labels)
# run_both(LinearRegression(), Normalizer(), all_inputs, all_outputs,
#          all_training_inputs, all_training_outputs,
#          all_test_inputs, all_test_outputs, all_labels)

#
# run(BatchGradientDescent(learning_rate=0.00001), Normalizer(), all_training_inputs, all_training_outputs,
#     all_test_inputs, all_test_outputs, all_labels, iterations=10000)
# run(ManualBatchGradientDescent(learning_rate=0.00001), Normalizer(), all_training_inputs, all_training_outputs,
#     all_test_inputs, all_test_outputs, all_labels, iterations=10000)

run(BatchGradientDescent(learning_rate=0.00001), ManualNormalizer(), all_inputs, all_outputs,
    all_inputs, all_outputs, all_labels, iterations=10000)
run(ManualBatchGradientDescent(learning_rate=0.00001), ManualNormalizer(), all_inputs, all_outputs,
    all_inputs, all_outputs, all_labels, iterations=10000)
