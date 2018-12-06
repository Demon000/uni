from Models.Item import Item

class Grade(Item):
    def __init__(self, id_, discipline_id, student_id, value):
        '''
        Initialize a grade.

        Args:
            id_ (int): The id of the grade.
            discipline_id (int): The id of the discipline that this grade has been given for.
            student_id (int): The id of the student that got this grade.
            value (int): The value of this grade.
        '''
        super().__init__(id_)
        self.__discipline_id = discipline_id
        self.__student_id = student_id
        self.__value = value

    def get_discipline_id(self):
        '''
        Returns:
            int: The id of the discipline that this grade has been given for.
        '''
        return self.__discipline_id

    def get_student_id(self):
        '''
        Returns:
            int: The id of the student that got this grade.
        '''
        return self.__student_id

    def get_value(self):
        '''
        Returns:
            int: The value of this grade.
        '''
        return self.__value

    def matches(self, discipline=None, student=None,
            discipline_id=None, student_id=None, value=None, test_fn=None):
        '''
        Check if this grade matches the passed arguments.

        Args:
            discipline (Discipline): A discipline that this grade is matched against.
            student (Student): A student that this grade is matched against.
            discipline_id (int, optional): A discipline id that this grade is matched against.
            student_id (int, optional): A student id that this grade is matched against.
            value (int, optional): A value that this grade is matched against.

        Returns:
            bool: Whether this grade matches the passed arguments.
        '''
        if discipline is not None and discipline.get_id() != self.__discipline_id:
            return False

        if student is not None and student.get_id() != self.__student_id:
            return False

        if discipline_id is not None and discipline_id != self.__discipline_id:
            return False

        if student_id is not None and student_id != self.__student_id:
            return False

        if value is not None and value != self.__value:
            return False

        if test_fn is not None and not test_fn(self):
            return False

        return True

    @staticmethod
    def serialize(grade):
        '''
        Returns:
            A serialized version of the grade.
        '''
        serialization = '{}\t{}\t{}\t{}'.format(grade.get_id(), grade.get_discipline_id(),
                grade.get_student_id(), grade.get_value())
        return serialization

    @staticmethod
    def deserialize(serialization):
        '''
        Deserialize a given serialization into a Grade.

        Args:
            serialization (str): The serialization to deserialize.

        Returns:
            Grade: A new grade instance deserialized from the given serialization.
        '''
        args = serialization.split('\t')
        return Grade(*args)
