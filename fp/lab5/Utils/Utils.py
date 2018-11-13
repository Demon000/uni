def validate_int(value, min_value=None, max_value=None, name='Value'):
    if type(value) is not int:
        raise ValueError('{} must be an integer.'.format(name))

    if min_value is not None and value < min_value:
        raise ValueError('{} must be larger than {}.'.format(name, min_value - 1))

    if max_value is not None and value > max_value:
        raise ValueError('{} must be smaller than {}.'.format(name, max_value + 1))

def validate_str(value, length=None, name='Value'):
    if type(value) is not str:
        raise ValueError('{} must be a string.'.format(name))

    if length is not None and length > len(value):
        raise ValueError('{} must be at least {} characters long.'.format(name, length))
