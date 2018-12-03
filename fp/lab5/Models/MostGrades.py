class MostGrades():
    def __init__(self, student, no_grades, over_value):
        '''
        Initialize a data transfer object representing the student with the
        most grades over a certain value.

        Args:
            student (Student): The student with the most grades.
            no_grades (int): The number of grades.
            over_value (int): The value over which grades are counted.
        '''
        self.__student = student
        self.__no_grades = no_grades
        self.__over_value = over_value

    def __str__(self):
        '''
        Returns:
            str: An user-friendly representation of the stored data.
        '''
        return '{} has {} grades over {}'.format(self.__student.get_name(),
                self.__no_grades, self.__over_value)

    def get_no_grades(self):
        '''
        Returns:
            int: The number of grades.
        '''
        return self.__no_grades
