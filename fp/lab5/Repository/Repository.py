class Repository():
    def __init__(self):
        '''
        Initialize a repository.
        '''
        self.__items = []

    def add(self, item):
        '''
        Add an item to the repository.

        Args:
            item (Item): The item to be added.

        Raises:
            ValueError: If an equal item already exists.
        '''
        self.__items.append(item)
        return item

    def get(self):
        '''
        Returns:
            list: A copy of the items list.
        '''
        items = self.__items[:]
        return items

    def get_matching(self, *args, **kwargs):
        '''
        Get all the items that match the passed arguments.

        Args:
            Same arguments as Item.matches().

        Returns:
            list: A list of the matching items.
        '''
        matching_items = []

        for item in self.__items:
            if item.matches(*args, **kwargs):
                matching_items.append(item)

        return matching_items

    def update(self, item, *args, **kwargs):
        '''
        Update the item using the passed arguments.

        Args:
            item (Item): The item to be updated.
        '''
        item.set_multiple(*args, **kwargs)

    def remove(self, item):
        '''
        Remove the passed item from the repository.

        Args:
            item (Item): The item to be removed.

        Raises:
            ValueError: If the item cannot be found in this repository.
        '''
        try:
            self.__items.remove(item)
        except ValueError:
            raise ValueError('Repository does not contain this item.')

    def remove_matching(self, *args, **kwargs):
        '''
        Remove all the items that match the passed arguments.

        Args:
            Same arguments as Item.matches().

        Returns:
            list: A list of the removed items.
        '''
        removed_items = self.get_matching(*args, **kwargs)

        for item in removed_items:
            self.remove(item)

        return removed_items
