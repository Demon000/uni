def is_valid_unsigned(value, min_=None, max_=None):
    '''
    Checks if the passed value is an int and is between
    {min} and {max} if those are not None.
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

def bind_fn(fn, *bind_args, **bind_kwargs):
    def binded(*new_args, **new_kwargs):
        fn(*(bind_args + new_args), **(bind_kwargs + new_kwargs))

    return binded
