class Item():
    def __init__(self, id_):
        '''
        Initialize an item.

        Args:
            id_ (int): The id_ of the item.
        '''
        self.__id = id_

    def get_id(self):
        '''
        Returns:
            int: The id of this item.
        '''
        return self.__id

    def __eq__(self, other):
        '''
        Returns:
            bool: Whether this item matches the other item.
        '''
        return self.get_id() == other.get_id()
