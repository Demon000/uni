from Collection.Item import Item

class Grade(Item):
    def __init__(self, id_, discipline_id, student_id, value):
        '''
        Initialize a grade and inherit from item.

        Args:
            discipline_id (int): The id of the discipline that this grade has
                been given for.
            student_id (int): The id of the student that got this grade.
            value (int): The value of this grade.
        '''
        super().__init__(id_)
        self.__discipline_id = discipline_id
        self.__student_id = student_id
        self.__value = value

    def __str__(self):
        '''
        Returns:
            str: An user-friendly representation of the stored data.
        '''
        return 'Student ID: {}, Discipline ID: {}, Grade: {}'.format(self.__student_id, self.__discipline_id, self.__value)

    def get_value(self):
        '''
        Returns:
            int: The value of this grade.
        '''
        return self.__value

    def matches(self, id_=None, discipline_id=None, student_id=None, value=None):
        '''
        Check if this grade matches the passed arguments.

        Args:
            id_ (int, optional): An id that this grade is matched against.
            discipline_id (int, optional): A discipline id that this grade is matched against.
            student_id (int, optional): A student id that this grade is matched against.
            value (int, optional): A value that this grade is matched against.

        Returns:
            bool: Whether this grade matches the passed arguments.
        '''
        if not super().matches(id_):
            return False

        if discipline_id is not None and discipline_id != self.__discipline_id:
            return False

        if student_id is not None and student_id != self.__student_id:
            return False

        return True
