from Utils.Utils import validate_int

class GradeValidator():
    def validate_value(self, value):
        '''
        Validate a grade value.

        Args:
            value (int): The value to be validated.

        Raises:
            ValueError: If the value is invalid.
        '''
        validate_int(value, 1, 10, 'Grade')
