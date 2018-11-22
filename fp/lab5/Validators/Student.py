from Utils.Utils import validate_str

class StudentValidator():
    def validate_name(self, name):
        '''
        Validate a student name.

        Args:
            name (str): The name to be validated.

        Raises:
            ValueError: If the name is invalid.
        '''
        validate_str(name, 1, 'Student name')
