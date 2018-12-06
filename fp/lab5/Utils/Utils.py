from difflib import SequenceMatcher

from Errors.Errors import ValidationError

def validate_int(value, min_value=None, max_value=None, name='Value'):
    if min_value is not None and value < min_value:
        raise ValidationError('{} must be larger than {}.'.format(name, min_value - 1))

    if max_value is not None and value > max_value:
        raise ValidationError('{} must be smaller than {}.'.format(name, max_value + 1))

def validate_str(value, length=None, name='Value'):
    if length is not None and length > len(value):
        raise ValidationError('{} must be at least {} characters long.'.format(name, length))

def get_similarity(one, other):
    sequence = SequenceMatcher(None, one, other)
    return sequence.ratio()
