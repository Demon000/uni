from Utils.Utils import validate_str

class Discipline():
    def __init__(self, name, professor):
        '''
        Initialize a discipline.

        Args:
            name (str): The name of this discipline.
            professor (str): The name of name of professor teaching this discipline.
        '''
        self.__name = name
        self.__professor = professor

    def __str__(self):
        '''
        Returns:
            str: An user-friendly representation of the stored data.
        '''
        return 'Name: {}, Professor: {}'.format(self.__name, self.__professor)

    def get_name(self):
        '''
        Returns:
            str: The name of this discipline.
        '''
        return self.__name

    def get_professor(self):
        '''
        Returns:
            str: The name of professor teaching this discipline.
        '''
        return self.__professor

    def set_name(self, name):
        '''
        Args:
            name (str): A new name for this discipline.
        '''
        self.__name = name

    def set_professor(self, professor):
        '''
        Args:
            professor (str): The new professor teaching this discipline.
        '''
        self.__professor = professor

    @staticmethod
    def validate_name(name):
        '''
        Validate a discipline name.

        Args:
            name (str): The name to be validated.

        Raises:
            ValueError: If the name is invalid.
        '''
        validate_str(name, 'Discipline name')

    @staticmethod
    def validate_professor(professor):
        '''
        Validate a professor name.

        Args:
            name (str): The name to be validated.

        Raises:
            ValueError: If the name is invalid.
        '''
        validate_str(professor, 'Professor name')
