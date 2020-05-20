import csv
from random import shuffle


def extract_columns_from_csv(file_path, indices, cell_type=float, unwrap_single_column=True):
    data = []
    with open(file_path) as file:
        csv_reader = csv.reader(file, delimiter=",")
        for row_data in csv_reader:
            data.append(row_data)

    rows = []
    for row_data in data:
        row = []
        for index in indices:
            cell_data = cell_type(row_data[index])
            row.append(cell_data)

        rows.append(row)

    if len(rows) != 0 and len(rows[0]) == 1 and unwrap_single_column:
        rows = [r[0] for r in rows]

    return rows


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
