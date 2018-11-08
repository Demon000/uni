class Item():
    def __init__(self, id_):
        '''
        Initialize an item.

        Args:
            id_ (int): The id of this item.
        '''
        self.id_ = id_

    def __eq__(self, other):
        '''
        Returns:
            bool: Whether this item is equal to the other item.
        '''
        return self.matches(other.id_)

    def __str__(self):
        '''
        Returns:
            str: An user-friendly representation of the stored data.
        '''
        return 'Id: {}'.format(self.id_)

    def get_id(self):
        '''
        Returns:
            int: The id of this item.
        '''
        return self.id_

    def matches(self, id_=None):
        '''
        Returns:
            bool: Whether this item matches the passed arguments.
        '''
        if id_ is not None and id_ != self.id_:
            return False

        return True
