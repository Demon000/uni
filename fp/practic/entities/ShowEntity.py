class ShowEntity():
    def __init__(self, name, type_, length, description):
        '''
        Initialize a show.

        Args:
            name (str): The name of the show.
            type_ (str): The type of the show.
            length (int): The duration of the show.
            description (str): The description of the show.
        '''
        self.__name = name
        self.__type = type_
        self.__length = length
        self.__description = description

    def __str__(self):
        '''
        Returns:
            str: An user-friendly representation of the stored data.
        '''
        return '{} {} {} {}'.format(self.__name, self.__type, self.__description, self.__length)

    def __eq__(self, other):
        return self.matches(other.get_name(), other.get_type())

    def matches(self, name, type_):
        '''
        Check if this show matches the given parameters.

        Args:
            name (str): The name to check against the show.
            type_ (str): The type to check against the show.

        Returns:
            bool: Whether the show matches or not.
        '''
        return self.__name == name and self.__type == type_

    def get_name(self):
        '''
        Returns:
            str: The name of the show.
        '''
        return self.__name

    def get_type(self):
        '''
        Returns:
            str: The type of the show.
        '''
        return self.__type

    def get_length(self):
        '''
        Returns:
            int: The length of the show.
        '''
        return self.__length

    def get_description(self):
        '''
        Returns:
            str: The description of the show.
        '''
        return self.__description

    def set_length(self, length):
        '''
        Set the length of the show.

        Args:
            length (int): The new length.
        '''
        self.__length = length

    def set_description(self, description):
        '''
        Set the description of the show.

        Args:
            description (str): The new description.
        '''
        self.__description = description

    def serialize(self):
        '''
        Returns:
            str: A serialized version of the show, to be used for saving.
        '''
        return '{},{},{},{}\n'.format(self.__name, self.__type, self.__length, self.__description)

    @staticmethod
    def deserialize(serialization):
        '''
        Returns:
            ShowEntity: A show generated from the given serialization.
        '''
        parts = serialization.strip().split(',')

        if len(parts) != 4:
            raise ValueError('Serialization is invalid.')

        name = parts[0]
        type_ = parts[1]
        length = int(parts[2])
        description = parts[3]

        show = ShowEntity(name, type_, length, description)

        return show
