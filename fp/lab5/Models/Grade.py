from Models.Item import Item

class Grade(Item):
    def __init__(self, id_, discipline, student, value):
        '''
        Initialize a grade.

        Args:
            id_ (int): The id of the grade.
            discipline (Discipline): The discipline that this grade has been given for.
            student (Student): The student that got this grade.
            value (int): The value of this grade.
        '''
        super().__init__(id_)
        self.__discipline = discipline
        self.__student = student
        self.__value = value

    def __str__(self):
        '''
        Returns:
            str: An user-friendly representation of the stored data.
        '''
        return 'Student: {}, Discipline: {}, Grade: {}' \
                .format(self.__student.get_name(), self.__discipline.get_name(), self.__value)

    def get_discipline(self):
        '''
        Returns:
            Discipline: The discipline that this grade has been given for.
        '''
        return self.__discipline

    def get_student(self):
        '''
        Returns:
            Student: The student that got this grade.
        '''
        return self.__student

    def get_value(self):
        '''
        Returns:
            int: The value of this grade.
        '''
        return self.__value

    def matches(self, discipline=None, student=None, value=None, test_fn=None):
        '''
        Check if this grade matches the passed arguments.

        Args:
            discipline (Discipline): A discipline that this grade is matched against.
            student (Student): A student that this grade is matched against.
            value (int, optional): A value that this grade is matched against.

        Returns:
            bool: Whether this grade matches the passed arguments.
        '''
        if discipline is not None and discipline != self.__discipline:
            return False

        if student is not None and student != self.__student:
            return False

        if value is not None and value != self.__value:
            return False

        if test_fn is not None and not test_fn(self):
            return False

        return True
