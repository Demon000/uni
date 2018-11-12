from Collection.Item import Item
from Utils.Utils import validate_int

class Grade(Item):
    def __init__(self, discipline, student, value):
        '''
        Initialize a grade and inherit from item.

        Args:
            discipline_id (int): The id of the discipline that this grade has
                been given for.
            student_id (int): The id of the student that got this grade.
            value (int): The value of this grade.
        '''
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

    def get_value(self):
        '''
        Returns:
            int: The value of this grade.
        '''
        return self.__value

    def matches(self, discipline=None, student=None, value=None):
        '''
        Check if this grade matches the passed arguments.

        Args:
            discipline_id (int, optional): A discipline id that this grade is matched against.
            student_id (int, optional): A student id that this grade is matched against.
            value (int, optional): A value that this grade is matched against.

        Returns:
            bool: Whether this grade matches the passed arguments.
        '''
        if discipline is not None and discipline != self.__discipline:
            return False

        if student is not None and student != self.__student:
            return False

        return True

    @staticmethod
    def validate_value(value):
        '''
        Validate a grade value.

        Args:
            value (int): The value to be validated.

        Raises:
            ValueError: If the value is invalid.
        '''
        validate_int(value, 1, 10, 'Grade')
