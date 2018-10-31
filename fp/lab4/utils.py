import json

def is_valid_unsigned(value, min_=None, max_=None):
    '''
    Checks if the passed value is a valid int.

    Args:
        min_ (int, optional): The minimum which the passed value is allowed to be.
        min_ (int, optional): The maximum which the passed value is allowed to be.
    '''
    if type(value) is not int:
        return False

    if value < 0:
        return False

    if min_ is not None and value < min_:
        return False

    if max_ is not None and value > max_:
        return False

    return True

def save_as_json(data, file_path):
    try:
        with open(file_path, 'w') as file_data:
            json.dump(data, file_data)
    except IOError:
        raise IOError('Failed to write data to {}'.format(file_path))

def load_from_json(file_path):
    try:
        with open(file_path, 'r') as file_data:
            return json.load(file_data)
    except IOError:
        raise IOError('Failed to read data from {}'.format(file_path))
