class Collection():
    def __init__(self):
        '''
        Initialize a collection.
        '''
        self.__items = []

    def add(self, item):
        '''
        Add an item to the collection.

        Args:
            item (Item): The item to be added.

        Raises:
            ValueError: If an equal item already exists.
        '''
        self.__items.append(item)

    def get(self):
        '''
        Returns:
            list: A copy of the items list.
        '''
        items = self.__items[:]
        return items

    def remove(self, item):
        '''
        Remove the passed item from the collection.

        Args:
            item (Item): The item to be removed.

        Raises:
            ValueError: If the item cannot be found in this collection.
        '''
        try:
            self.__items.remove(item)
        except ValueError:
            raise ValueError('Collection does not contain this item.')
