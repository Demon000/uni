class Collection():
    def __init__(self, Type):
        '''
        Initialize a collection.

        Args:
            Type (Class): The class initializer for the items.
        '''
        self.__items = []
        self.__Type = Type

    def contains(self, other):
        '''
        Returns:
            bool: Whether there is any item in this list
            equal with the given item.
        '''
        for item in self.__items:
            if item == other:
                return True

        return False

    def add(self, item):
        '''
        Add an item to the collection.

        Args:
            item (Item): The item to be added.

        Raises:
            ValueError: If an equal item already exists.
        '''
        if self.contains(item):
            raise ValueError('Collection already contains an equivalent item '
                    'of type {}'.format(self.__Type.__name__))

        self.__items.append(item)

    def create(self, *args, **kwargs):
        '''
        Create an item using the passed arguments and assign it an unique id.

        Args:
            Same arguments as Type().

        Returns:
            Item: The newly created item.
        '''
        item = self.__Type(*args, **kwargs)

        self.add(item)

        return item

    def get(self):
        '''
        Returns:
            list: A copy of the items list.
        '''
        items = self.__items[:]
        return items

    def find_matching(self, *args, **kwargs):
        '''
        Find the items that match the passed arguments.

        Args:
            Same arguments as Item.matches().

        Returns:
            list: A list containing the matching items.
        '''
        matching_items = []

        for item in self.__items:
            if item.matches(*args, **kwargs):
                matching_items.append(item)

        return matching_items

    def find_one_matching(self, *args, **kwargs):
        '''
        Find the item that matches the passed arguments.

        Args:
            Same arguments as Item.matches().

        Returns:
            Item: The matching item or None if there is no such item.
        '''
        matching_items = self.find_matching(*args, **kwargs)

        if len(matching_items):
            item = matching_items[0]
        else:
            item = None

        return item

    def remove_matching(self, *args, **kwargs):
        '''
        Find the items that match the passed arguments and
        remove them.

        Args:
            Same arguments as Item.matches().

        Returns:
            list: A list containing the deleted items.
        '''
        removed_items = []
        left_items = []

        for item in self.__items:
            if item.matches(*args, **kwargs):
                removed_items.append(item)
            else:
                left_items.append(item)

        self.__items = left_items

        return removed_items

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
