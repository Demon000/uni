class Item():
    def __init__(self, id_):
        '''
        Initialize an item.

        Args:
            id_ (int): The id of this item.
        '''
        self.__id = id_

    def __eq__(self, other):
        '''
        Returns:
            bool: Whether this item is equal to the other item.
        '''
        return self.matches(other.__id)

    def __str__(self):
        '''
        Returns:
            str: An user-friendly representation of the stored data.
        '''
        return 'Id: {}'.format(self.__id)

    def get_id(self):
        '''
        Returns:
            int: The id of this item.
        '''
        return self.__id

    def matches(self, id_=None):
        '''
        Returns:
            bool: Whether this item matches the passed arguments.
        '''
        if id_ is not None and id_ != self.__id:
            return False

        return True
