from Collection.Item import Item
from Utils.Utils import validate_str

class Student(Item):
    def __init__(self, id_, name):
        '''
        Initialize a student and inherit from item.
        Validate the passed arguments.

        Args:
            id_ (int): The id of this item.
            name (str): The name of this student.
        '''

        validate_str(name, 'Student name')

        super().__init__(id_)
        self.__name = name

    def __str__(self):
        '''
        Returns:
            str: An user-friendly representation of the stored data.
        '''
        return 'ID: {}, Name: {}'.format(self.get_id(), self.__name)

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
