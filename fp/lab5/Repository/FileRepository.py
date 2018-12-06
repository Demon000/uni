import os

from Errors.Errors import RepositoryError

class FileRepository():
    def __init__(self, path, serialize, deserialize):
        '''
        Initialize a file repository.

        Args:
            path (str): The path to the file used for persistent storage of
                the items.
            serialize (function): A function used for serializing the items of
                the repository.
            serialize (function): A function used for deserializing the contents
                of the repository file.
        '''
        self.__path = path
        self.__serialize = serialize
        self.__deserialize = deserialize

    def __create(self):
        '''
        Create the file used for persistent storage if it doesn't exist.
        '''
        if os.path.exists(self.__path):
            return

        with open(self.__path, 'w') as file:
            pass

    def __save(self, items):
        '''
        Save the items to the repository file.

        Args:
            items (list): The items to save.
        '''
        serialized_items = []
        for item in items:
            item_serialization = self.__serialize(item)
            serialized_items.append(item_serialization)

        self.__create()
        with open(self.__path, 'w') as file:
            file.writelines(serialized_items)

    def __load(self):
        '''
        Load items from the repository file.

        Returns:
            list: The items loaded from the repository file.
        '''
        self.__create()
        with open(self.__path, 'r') as file:
            serialized_items = file.readlines()

        items = []
        for item_serialization in serialized_items:
            item = self.__deserialize(item_serialization)
            items.append(item)

        return items

    def append(self, item):
        '''
        Append the given item to the repository file.

        Args:
            item (Item): The item to add to the repository file.
        '''
        item_serialization = self.__serialize(item)

        self.__create()
        with open(self.__path, 'a') as file:
            file.write(item_serialization)
            file.write('\n')

    def get_available_id(self):
        '''
        Returns:
            int: The first available id.
        '''
        available_id = 0

        items = self.__load()
        for item in items:
            if item.get_id() >= available_id:
                available_id = item.get_id() + 1

        return available_id

    def contains(self, item):
        '''
        Returns:
            bool: Whether the repository contains an item equal to the passed one.
        '''
        items = self.__load()
        for other in items:
            if item == other:
                return True

        return False

    def add(self, item):
        '''
        Add an item to the repository.

        Args:
            item (Item): The item to be added.

        Raises:
            RepositoryError: If an equal item already exists.
        '''
        if self.contains(item):
            raise RepositoryError('Item already exists.')

        self.append(item)

        return item

    def get(self):
        '''
        Returns:
            list: A copy of the items list.
        '''
        items = self.__load()
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

        items = self.__load()
        for item in items:
            if item.matches(*args, **kwargs):
                matching_items.append(item)

        return matching_items

    def get_one_matching(self, *args, **kwargs):
        '''
        Get the first item that matches the passed arguments.

        Args:
            Same arguments as Item.matches().

        Returns:
            Item: The first item that matches the passed arguments.
        '''
        matching_items = self.get_matching(*args, **kwargs)

        if len(matching_items):
            item = matching_items[0]
        else:
            item = None

        return item

    def update(self, item, *args, **kwargs):
        '''
        Update the item using the passed arguments.

        Args:
            item (Item): The item to be updated.
        '''
        items = self.__load()

        for other in items:
            if other == item:
                other.set_multiple(*args, **kwargs)

        self.__save(items)

    def remove(self, item):
        '''
        Remove the passed item from the repository.

        Args:
            item (Item): The item to be removed.

        Raises:
            RepositoryError: If the item cannot be found in this repository.
        '''
        items = self.__load()
        removed = False

        for other in items:
            if other == item:
                items.remove(other)
                removed = True

        self.__save(items)

        if not removed:
            raise RepositoryError('Repository does not contain this item.')

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
