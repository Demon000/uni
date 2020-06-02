import os

import matplotlib.image as mpimg
import numpy as np

SEPIA_DATA_DIRECTORY = 'sepia_data'


def sepia_load_data():
    inputs = []
    outputs = []

    for filename in os.listdir(SEPIA_DATA_DIRECTORY):
        if not filename.endswith('.png'):
            continue

        path = os.path.join(SEPIA_DATA_DIRECTORY, filename)

        image = mpimg.imread(path)
        inputs.append(image)

        name = os.path.splitext(filename)[0]
        number = int(name)
        if number <= 45:
            is_sepia = 0
        else:
            is_sepia = 1

        outputs.append([is_sepia])

    return np.array(inputs), np.array(outputs)
