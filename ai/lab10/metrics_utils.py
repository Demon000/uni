from math import log

from tabulate import tabulate


def check_same_size(first, second, bi_dimensional=True):
    assert len(first) == len(second)
    assert len(first) != 0

    if not bi_dimensional:
        return

    first_element = first[0]
    if not isinstance(first_element, list):
        return

    l = len(first[0])
    for i in range(len(first)):
        assert len(first[i]) == l
        assert len(second[i]) == l


def mc_performance(predicted_classes, actual_classes):
    check_same_size(predicted_classes, actual_classes)
    labels = list(set(predicted_classes + actual_classes))
    no_samples = len(predicted_classes)

    accuracies = []
    precisions = []
    recalls = []
    for label in labels:
        true_positives = sum(1 for i in range(no_samples) if predicted_classes[i] == label
                             and actual_classes[i] == label)
        false_positives = sum(1 for i in range(no_samples) if predicted_classes[i] == label
                              and actual_classes[i] != label)
        true_negatives = sum(1 for i in range(no_samples) if predicted_classes[i] != label
                             and actual_classes[i] != label)
        false_negatives = sum(1 for i in range(no_samples) if predicted_classes[i] != label
                              and actual_classes[i] == label)

        # what proportion of actual positives and negatives are correctly predicted?
        accuracy = (true_positives + true_negatives) / \
                   (true_positives + false_positives + true_negatives + false_negatives)

        # what proportion of predicted positives is actually positive?
        try:
            precision = true_positives / (true_positives + false_positives)
        except ZeroDivisionError:
            precision = 0

        # what proportion of actual positives is correctly predicted?
        try:
            recall = true_positives / (true_positives + false_negatives)
        except ZeroDivisionError:
            recall = 0

        accuracies.append(accuracy)
        precisions.append(precision)
        recalls.append(recall)

    return labels, precisions, recalls, accuracies


def mc_loss(classes, predicted_probabilities, actual_classes):
    no_samples = len(predicted_probabilities)
    no_classes = len(classes)

    total_sums = [0 for _ in range(no_classes)]
    for i in range(no_samples):
        actual_class = actual_classes[i]
        predicted_probability = predicted_probabilities[i]

        for class_index in range(no_classes):
            print(classes, actual_class)
            if classes[class_index] == actual_class:
                total_sums[class_index] -= log(predicted_probability[class_index])

    return total_sums


def print_mc_performance(predicted_classes, actual_classes):
    labels, precisions, recalls, accuracies = mc_performance(predicted_classes, actual_classes)
    no_labels = len(labels)

    labels = [''] + labels + ['Average']
    accuracies = ['Accuracy'] + [str(x) for x in accuracies] + [str(sum(accuracies) / no_labels)]
    precisions = ['Precision'] + [str(x) for x in precisions] + [str(sum(precisions) / no_labels)]
    recalls = ['Recall'] + [str(x) for x in recalls] + [str(sum(recalls) / no_labels)]
    print(tabulate([accuracies, precisions, recalls], headers=labels, tablefmt="fancy_grid"))
