from Utils.Utils import validate_int

class Grade():
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
