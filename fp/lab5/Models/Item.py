class Item():
    def __init__(self, id_):
        '''
        Initialize an item.

        Args:
            id_ (int): The id_ of the item.
        '''
        self.__id = id_

    def __eq__(self, other):
        '''
        Returns:
            bool: Whether this item matches the other item.
        '''
        return self.get_id() == other.get_id()

    def get_id(self):
        '''
        Returns:
            int: The id of this item.
        '''
        return self.__id

    def matches(self, id_=None):
        '''
        Check if this item matches the passed arguments.

        Args:
            id_ (int, optional): An id that this item is matched against.

        Returns:
            bool: Whether this item matches the passed arguments.
        '''
        if id_ is not None and id_ != self.__id:
            return False

        return True
