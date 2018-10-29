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

def bind_fn(fn, *bind_args, **bind_kwargs):
    '''
    Binds a function to the passed arguments.

    Args:
        fn (function): A function to bind the passed arguments to.

    Returns:
        function: A new function which calls the passed function with the
            provided arguments.
    '''
    def binded():
        return fn(*bind_args, **bind_kwargs)

    return binded
