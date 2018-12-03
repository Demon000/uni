class AverageGrade():
    def __init__(self, student, value):
        '''
        Initialize a data transfer object used for representing the average
        grade for a student.

        Args:
            student (Student): The student which has this average grade.
            value (float): The value of this average grade.
        '''
        self.__student = student
        self.__value = value

    def __str__(self):
        '''
        Returns:
            str: An user-friendly representation of the stored data.
        '''
        return 'Name: {}, Average grade: {}'.format(self.__student.get_name(), self.get_value())

    def get_student(self):
        '''
        Returns:
            Student: The student which has this average grade.
        '''
        return self.__student

    def get_value(self):
        '''
        Returns:
            float: The value of this average grade.
        '''
        return self.__value
