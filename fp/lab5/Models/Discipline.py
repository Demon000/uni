from Models.Item import Item

class Discipline(Item):
    def __init__(self, id_, name, professor):
        '''
        Initialize a discipline.

        Args:
            id_ (int): The id of the discipline.
            name (str): The name of this discipline.
            professor (str): The name of name of professor teaching this discipline.
        '''
        super().__init__(id_)
        self.__name = name
        self.__professor = professor

    def __str__(self):
        '''
        Returns:
            str: An user-friendly representation of the stored data.
        '''
        return 'Name: {}, Professor: {}'.format(self.__name, self.__professor)

    def get_name(self):
        '''
        Returns:
            str: The name of this discipline.
        '''
        return self.__name

    def get_professor(self):
        '''
        Returns:
            str: The name of professor teaching this discipline.
        '''
        return self.__professor

    def set_name(self, name):
        '''
        Args:
            name (str): A new name for this discipline.
        '''
        self.__name = name

    def set_professor(self, professor):
        '''
        Args:
            professor (str): The new professor teaching this discipline.
        '''
        self.__professor = professor

    def set_multiple(self, name=None, professor=None):
        '''
        Args:
            name (str): A new name for this discipline.
            professor (str): The new professor teaching this discipline.
        '''
        if name is not None:
            self.set_name(name)

        if professor is not None:
            self.set_professor(professor)

    @staticmethod
    def serialize(discipline):
        '''
        Returns:
            A serialized version of the discipline.
        '''
        serialization = '{}\t{}\t{}'.format(discipline.get_id(), discipline.get_name(),
                discipline.get_professor())
        return serialization

    @staticmethod
    def deserialize(serialization):
        '''
        Deserialize a given serialization into a Discipline.

        Args:
            serialization (str): The serialization to deserialize.

        Returns:
            Discipline: A new discipline instance deserialized from the given serialization.
        '''
        args = serialization.split('\t')
        id_ = int(args[0])
        name = args[1]
        professor = args[2]
        discipline = Discipline(id_, name, professor)
        return discipline
