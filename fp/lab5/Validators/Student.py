from Utils.Utils import validate_str

class StudentValidator():
    @staticmethod
    def validate_name(name):
        '''
        Validate a student name.

        Args:
            name (str): The name to be validated.

        Raises:
            ValueError: If the name is invalid.
        '''
        validate_str(name, 1, 'Student name')
