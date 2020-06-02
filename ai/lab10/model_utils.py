import pickle


def save_model_to_file(file_path, model):
    with open(file_path, 'wb') as file:
        pickle.dump(model, file)


def read_model_from_file(file_path):
    with open(file_path, 'rb') as file:
        return pickle.load(file)
