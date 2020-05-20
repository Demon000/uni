from random import seed

from data_utils import extract_columns_from_csv, split_training_set
from logistic_regressor import LogisticRegressor
from manual_logistic_regressor import ManualMultiClassLogisticRegressor
from metrics_utils import print_mc_performance, mc_loss
from sklearn.preprocessing import StandardScaler

import matplotlib.pyplot as plt


seed(5)


def plot_losses(losses):
    plt.plot(range(len(losses)), losses)
    plt.xlabel("Iteration")
    plt.ylabel("Loss")
    plt.show()


def run_with_regressor(regressor, training_inputs, training_outputs, test_inputs, test_outputs, iterations):
    last_predicted_outputs = None
    last_loss = None
    losses = []

    for i in range(iterations):
        regressor.fit(training_inputs, training_outputs)
        last_predicted_outputs = regressor.predict(test_inputs)

        probabilities = regressor.predict_probabilities(test_inputs)
        last_loss = mc_loss(regressor.classes, probabilities, test_outputs)
        losses.append(last_loss)

    if iterations != 1:
        plot_losses(losses)

    print(f"Loss: {last_loss}")

    print_mc_performance(last_predicted_outputs, test_outputs)


LABEL_COLUMN_INDEX = 4
all_inputs = extract_columns_from_csv('iris.data', range(LABEL_COLUMN_INDEX))
all_outputs = extract_columns_from_csv('iris.data', [LABEL_COLUMN_INDEX], str)
all_training_inputs, all_training_outputs, all_test_inputs, all_test_outputs = \
    split_training_set(all_inputs, all_outputs, 0.8)
scaler = StandardScaler()

scaler.fit(all_training_inputs)
all_training_inputs = scaler.transform(all_training_inputs)
all_test_inputs = scaler.transform(all_test_inputs)


ITERATIONS = 1000
LEARNING_RATE = 0.0001
# run_with_regressor(LogisticRegressor(),
#                    all_training_inputs, all_training_outputs,
#                    all_test_inputs, all_test_outputs, 1)
# run_with_regressor(ManualMultiClassLogisticRegressor(learning_rate=LEARNING_RATE),
#                    all_training_inputs, all_training_outputs,
#                    all_test_inputs, all_test_outputs, ITERATIONS)

run_with_regressor(LogisticRegressor(),
                   all_inputs, all_outputs,
                   all_inputs, all_outputs, 1)
run_with_regressor(ManualMultiClassLogisticRegressor(learning_rate=LEARNING_RATE),
                   all_inputs, all_outputs,
                   all_inputs, all_outputs, ITERATIONS)
