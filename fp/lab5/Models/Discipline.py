from Collection.Item import Item
from Utils.Utils import validate_str

class Discipline(Item):
    def __init__(self, id_, name, professor):
        '''
        Initialize a discipline and inherit from item.
        Validate the passed arguments.

        Args:
            id_ (int): The id of this item.
            name (str): The name of this discipline.
        '''

        validate_str(name, 'Discipline name')
        validate_str(professor, 'Professor name')

        super().__init__(id_)
        self.__name = name
        self.__professor = professor

    def __str__(self):
        '''
        Returns:
            str: An user-friendly representation of the stored data.
        '''
        return 'ID: {}, Name: {}, Professor: {}'.format(self.get_id(), self.__name, self.__professor)

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
