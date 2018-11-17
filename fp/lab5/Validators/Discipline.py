from Utils.Utils import validate_str

class DisciplineValidator():
    @staticmethod
    def validate_name(name):
        '''
        Validate a discipline name.

        Args:
            name (str): The name to be validated.

        Raises:
            ValueError: If the name is invalid.
        '''
        validate_str(name, 1, 'Discipline name')

    @staticmethod
    def validate_professor(professor):
        '''
        Validate a professor name.

        Args:
            name (str): The name to be validated.

        Raises:
            ValueError: If the name is invalid.
        '''
        validate_str(professor, 1, 'Professor name')
