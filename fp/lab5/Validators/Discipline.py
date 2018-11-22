from Utils.Utils import validate_str

class DisciplineValidator():
    def validate_name(self, name):
        '''
        Validate a discipline name.

        Args:
            name (str): The name to be validated.

        Raises:
            ValueError: If the name is invalid.
        '''
        validate_str(name, 1, 'Discipline name')

    def validate_professor(self, professor):
        '''
        Validate a professor name.

        Args:
            name (str): The name to be validated.

        Raises:
            ValueError: If the name is invalid.
        '''
        validate_str(professor, 1, 'Professor name')
