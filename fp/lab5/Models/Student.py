from Utils.Utils import validate_str

class Student():
    def __init__(self, name):
        '''
        Initialize a student and inherit from item.

        Args:
            name (str): The name of this student.
        '''
        self.__name = name

    def __str__(self):
        '''
        Returns:
            str: An user-friendly representation of the stored data.
        '''
        return 'Name: {}'.format(self.__name)

    def get_name(self):
        '''
        Returns:
            str: The name of this student.
        '''
        return self.__name

    def set_name(self, name):
        '''
        Args:
            name (str): A new name for this student.
        '''
        self.__name = name

    @staticmethod
    def validate_name(name):
        '''
        Validate a student name.

        Args:
            name (str): The name to be validated.

        Raises:
            ValueError: If the name is invalid.
        '''
        validate_str(name, 'Student name')
