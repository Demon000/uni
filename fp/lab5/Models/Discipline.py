from Collection.Item import Item

class Discipline(Item):
    def __init__(self, id_, name):
        '''
        Initialize a discipline and inherit from item.

        Args:
            id_ (int): The id of this item.
            name (str): The name of this discipline.
        '''
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
            str: The name of this discipline.
        '''
        return self.__name

    def set_name(self, name):
        '''
        Args:
            name (str): A new name for this discipline.
        '''
        self.__name = name
