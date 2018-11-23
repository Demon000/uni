class Student():
    def __init__(self, name):
        '''
        Initialize a student.

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

    def set_multiple(self, name=None):
        '''
        Args:
            name (str): A new name for this student.
        '''
        if name is not None:
            self.set_name(name)
