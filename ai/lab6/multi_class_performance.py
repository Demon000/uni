from tabulate import tabulate

from checks import check_same_size


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
        precision = true_positives / (true_positives + false_positives)

        # what proportion of actual positives is correctly predicted?
        recall = true_positives / (true_positives + false_negatives)

        accuracies.append(accuracy)
        precisions.append(precision)
        recalls.append(recall)

    return labels, accuracies, precisions, recalls


def print_mc_performance(predicted_classes, actual_classes):
    labels, accuracies, precisions, recalls = mc_performance(predicted_classes, actual_classes)
    labels = [""] + labels
    accuracies = ["Accuracy"] + [str(x) for x in accuracies]
    precisions = ["Precision"] + [str(x) for x in precisions]
    recalls = ["Recall"] + [str(x) for x in recalls]
    print(tabulate([accuracies, precisions, recalls], headers=labels, tablefmt="fancy_grid"))


C = "Cat"
F = "Fish"
H = "Hen"

pc = [C, C, C, C, C, C, F, F, F, F, F, F, F, F, F, F, H, H, H, H, H, H, H, H, H]
cc = [C, C, C, C, H, F, C, C, C, C, C, C, H, H, F, F, C, C, C, H, H, H, H, H, H]
print_mc_performance(pc, cc)
