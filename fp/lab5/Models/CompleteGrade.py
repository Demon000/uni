class CompleteGrade():
    def __init__(self, grade, discipline, student):
        '''
        Initialize a data transfer object used for representing the complete
        structure for a grade, including a reference to the student and discipline.

        Args:
            grade (Grade): The given grade.
            discipline (Discipline): The discipline that this grade has been given for.
            student (Student): The student that got this grade.
        '''
        self.__grade = grade
        self.__discipline = discipline
        self.__student = student

    def __str__(self):
        '''
        Returns:
            str: An user-friendly representation of the stored data.
        '''
        return 'Student: {}, Discipline: {}, Grade: {}' \
                .format(self.__student.get_name(), self.__discipline.get_name(), self.get_value())

    def get_grade(self):
        '''
        Returns:
            Grade: The given grade.
        '''
        return self.__grade

    def get_value(self):
        '''
        Returns:
            int: The value of the given grade.
        '''
        return self.__grade.get_value()

    def get_discipline(self):
        '''
        Returns:
            int: The discipline that this grade has been given for.
        '''
        return self.__discipline

    def get_student(self):
        '''
        Returns:
            int: The student that got this grade.
        '''
        return self.__student
