class MostGrades():
    def __init__(self, student, no_grades, over_value):
        self.__student = student
        self.__no_grades = no_grades
        self.__over_value = over_value

    def __str__(self):
        return '{} has {} grades over {}'.format(self.__student.get_name(),
                self.__no_grades, self.__over_value)

    def get_no_grades(self):
        return self.__no_grades
