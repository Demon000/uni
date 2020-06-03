import pandas as pd
from sklearn.metrics import classification_report

from kmeans import KMeans

NO_ITERATIONS = 100

data = pd.read_csv('iris.data')
original_inputs = data[['SepalLengthCm', 'SepalWidthCm', 'PetalLengthCm', 'PetalWidthCm']]
original_outputs = data['Species']

all_inputs = original_inputs.apply(lambda x: (x - x.min()) / (x.max() - x.min()))
all_outputs = original_outputs

all_inputs = all_inputs.values
all_outputs = all_outputs.values

all_train_inputs = all_inputs
all_train_outputs = all_outputs
all_test_inputs = all_inputs
all_test_outputs = all_outputs


km = KMeans()
for _ in range(NO_ITERATIONS):
    km.fit(all_train_inputs, all_train_outputs)

predicted_outputs = km.predict(all_test_inputs)

print(classification_report(all_test_outputs, predicted_outputs))
