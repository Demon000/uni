from string import ascii_lowercase

import pandas as pd

from collections import Counter

from kmeans import KMeans

NO_ITERATIONS = 100

data = pd.read_csv('text.data')
all_inputs = data['Text']

allowed_characters = set(ascii_lowercase + ' ')
all_inputs = all_inputs.apply(lambda x: x.lower())
all_inputs = all_inputs.apply(lambda x: ''.join(c for c in x if c in allowed_characters))
all_inputs = all_inputs.apply(lambda x: Counter(x.split(' ')))
print(all_inputs)

all_outputs = data['Sentiment']
all_outputs = all_outputs.replace(['negative', 'positive'], [0, 1])
