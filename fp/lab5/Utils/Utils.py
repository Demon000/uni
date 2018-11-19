def validate_int(value, min_value=None, max_value=None, name='Value'):
    if min_value is not None and value < min_value:
        raise ValueError('{} must be larger than {}.'.format(name, min_value - 1))

    if max_value is not None and value > max_value:
        raise ValueError('{} must be smaller than {}.'.format(name, max_value + 1))

def validate_str(value, length=None, name='Value'):
    if length is not None and length > len(value):
        raise ValueError('{} must be at least {} characters long.'.format(name, length))

def input_value(message, type_cast=None, validate_fn=None, default=None):
    while True:
        try:
            raw_value = input(message)
            if type_cast is not None:
                value = type_cast(raw_value)
            else:
                value = raw_value

            validate_fn(value)
        except ValueError as ve:
            print(ve)
            if default is not None:
                print('Using default value.')
                value = default
            else:
                continue

        return value

def input_int(message, min_value=None, max_value=None):
    def validate(value):
        validate_int(value, min_value=min_value, max_value=max_value)

    return input_value(message, type_cast=int, validate_fn=validate)

def input_item(message, items):
    for index, item in enumerate(items):
        print('{}. {}'.format(index , item))

    index = input_int(message, min_value=0, max_value=len(items) - 1)
    return items[index]
