class Collection():
    def get_unique_id(self):
        next_id = self.next_id
        self.next_id += 1
        return next_id
        
    def __init__(self, Type):
        '''
        Initialize a collection.

        Args:
            Type (Class): The class initializer for the items.
        '''
        self.items = []
        self.Type = Type
        self.next_id = 0

    def contains(self, other):
        '''
        Returns:
            bool: Whether there is any item in this list
            equal with the given item.
        '''
        for item in self.items:
            if item == other:
                return True

        return False

    def create(self, *args, **kwargs):
        '''
        Create an item using the passed arguments and assign it an unique id.
        Add it to the expenses list.

        Args:
            Same arguments as Type(), except id_.

        Returns:
            Item: The newly created item.

        Raises:
            ValueError: If an equal item already exists.
        '''
        id_ = self.get_unique_id()
        item = self.Type(id_, *args, **kwargs)
        self.items.append(item)
        return item

    def get(self):
        '''
        Returns:
            list: A copy of the items list.
        '''
        items = self.items[:]
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

        for item in self.items:
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

    def delete_matching(self, *args, **kwargs):
        '''
        Find the items that match the passed arguments and
        remove them.

        Args:
            Same arguments as Item.matches().

        Returns:
            list: A list containing the deleted items.
        '''
        deleted_items = []
        left_items = []

        for item in self.items:
            if item.matches(*args, **kwargs):
                deleted_items.append(item)
            else:
                left_items.append(item)

        self.items = left_items

        return deleted_items
