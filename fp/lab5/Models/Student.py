from Models.Item import Item

class Student(Item):
    def __init__(self, id_, name):
        '''
        Initialize a student.

        Args:
            id_ (int): The id of the student.
            name (str): The name of this student.
        '''
        super().__init__(id_)
        self.__name = name

    def __str__(self):
        '''
        Returns:
            str: An user-friendly representation of the stored data.
        '''
        return 'Name: {}'.format(self.__name)

    def get_name(self):
        '''
        Returns:
            str: The name of this student.
        '''
        return self.__name

    def set_name(self, name):
        '''
        Args:
            name (str): A new name for this student.
        '''
        self.__name = name

    def set_multiple(self, name=None):
        '''
        Args:
            name (str): A new name for this student.
        '''
        if name is not None:
            self.set_name(name)

    @staticmethod
    def serialize(student):
        '''
        Returns:
            A serialized version of the student.
        '''
        serialization = '{}\t{}'.format(student.__id, student.__name)
        return serialization

    @staticmethod
    def deserialize(serialization):
        '''
        Deserialize a given serialization into a Student.

        Args:
            serialization (str): The serialization to deserialize.

        Returns:
            Student: A new student instance deserialized from the given serialization.
        '''
        args = serialization.split('\t')
        return Student(*args)
